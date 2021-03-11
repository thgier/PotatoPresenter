#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QCryptographicHash>
#include <charconv>
#include <QDir>
#include <QRegularExpression>

#include "parser.h"
#include "frame.h"
#include "box.h"
#include "imagebox.h"
#include "markdowntextbox.h"
#include "arrowbox.h"
#include "plaintextbox.h"
#include "linebox.h"
#include "codebox.h"

Parser::Parser(QString resourcepath)
    : mResourcepath(resourcepath)
{
}

void Parser::loadInput(QIODevice *input){
    mTokenizer.loadInput(input);
}

void Parser::loadInput(QByteArray input){
    mTokenizer.loadInput(input);
}

Preamble Parser::readPreamble() {
    while(!(mTokenizer.peekNext().mKind == Token::Kind::Command && mTokenizer.peekNext().mText == "\\frame")
          || mTokenizer.peekNext().mKind == Token::Kind::EndOfFile) {
        auto token = mTokenizer.next();
        if (token.mKind == Token::Kind::Command) {
            preambleCommand(token);
        }
        else if(token.mKind == Token::Kind::EndOfFile) {
            throw ParserError{"Expecting command", 0};
        }
        else{
            throw ParserError{"Expecting command", token.mLine};
        }
    }
    return mPreamble;
}

void Parser::preambleCommand(Token token) {
    if(token.mText == "\\usetemplate"){
        auto const nextToken = mTokenizer.next();
        if(nextToken.mKind != Token::Kind::Text) {
            throw ParserError{"Expecting template name", token.mLine};
            return;
        }
        mPreamble.templateName = nextToken.mText;
    }
    else if(token.mText == "\\setvar"){
        setVariable(token.mLine);
    }
}

FrameList Parser::readInput(){
    auto token = mTokenizer.next();
    while(token.mKind != Token::Kind::EndOfFile) {
        if (token.mKind == Token::Kind::Command) {
            command(token);
        }
        else{
            throw ParserError{"Expecting command", token.mLine};
        }
        token = mTokenizer.next();
    }
    for(auto const& frame: mFrameList.vector){
        frame->setVariable("%{totalpages}", QString::number(mFrameList.vector.size() - 1));
    }
    return mFrameList;
}

void Parser::command(Token token){
    if(token.mText == "\\frame"){
        newFrame(token.mLine);
    }
    else if(token.mText == "\\text"){
        newTextField(token.mLine);
    }
    else if(token.mText == "\\image"){
        newImage(token.mLine);
    }
    else if(token.mText == "\\body"){
        newBody(token.mLine);
    }
    else if(token.mText == "\\title"){
        newTitle(token.mLine);
    }
    else if(token.mText == "\\arrow"){
        newArrow(token.mLine);
    }
    else if(token.mText == "\\line"){
        newLine(token.mLine);
    }
    else if(token.mText == "\\pause"){
        applyPause();
    }
    else if(token.mText == "\\plaintext"){
        newPlainText(token.mLine);
    }
    else if(token.mText == "\\code"){
        newCodeBox(token.mLine);
    }
    else if(token.mText == "\\blindtext"){
        newBlindText(token.mLine);
    }
    else if(token.mText == "\\setvar"){
        setVariable(token.mLine);
    }
    else{
        throw ParserError{QString("Invalid command '%1'").arg(QString(token.mText)), token.mLine};
    }
}

void Parser::newFrame(int line){
    mPauseCount = 0;
    auto token = mTokenizer.next();
    Box::List templateBoxes;
    QString frameClass;
    if(token.mKind == Token::Kind::Argument){
        if(token.mText != "class"){
            throw ParserError{QString("Invalid argument '%1' for \\frame").arg(QString(token.mText)), token.mLine};
            return;
        }
        auto const tokenArgValue = mTokenizer.next();
        if(tokenArgValue.mKind != Token::Kind::ArgumentValue){
            throw ParserError{"Missing value for argument", token.mLine};
            return;
        }
        frameClass = tokenArgValue.mText;
        token = mTokenizer.next();
    }
    if(token.mKind != Token::Kind::Text || token.mText.isEmpty()) {
        throw ParserError{"Expecting frame id", line};
        return;
    }
    auto const id = QString(token.mText);
    for(auto const& frame: mFrameList.vector) {
        if(frame->id() == id){
            throw ParserError{QString("Duplicate frame ID '%1'").arg(id), line};
        }
    }
    mVariables["%{pagenumber}"] = QString::number(mFrameList.vector.size());
    if(mVariables.find("%{date}") == mVariables.end()){
        mVariables["%{date}"] = QDate::currentDate().toString();
    }
    if(mVariables.find("%{resourcepath}") == mVariables.end()){
        mVariables["%{resourcepath}"] = mResourcepath;
    }
    mFrameList.vector.push_back(std::make_shared<Frame>(id, mVariables, line));
    mFrameList.vector.back()->setTemplateBoxes(templateBoxes);
    mFrameList.vector.back()->setFrameClass(frameClass);
}

void Parser::newTextField(int line){
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }
    QString id;
    auto const boxStyle = readArguments(id);
    if(id.isEmpty()) {
        id = generateId("text", boxStyle.boxClass);
    }

    QString text = "";
    auto const peekNextKind = mTokenizer.peekNext().mKind;
    auto const peeknext = mTokenizer.peekNext();
    if(peekNextKind == Token::Kind::Text || peekNextKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<MarkdownTextBox>(text, boxStyle, id, line);
    textField->setBoxStyle(boxStyle);
    textField->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(textField);
}

void Parser::newImage(int line) {
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }
    QString id;
    auto boxStyle = readArguments(id);
    if(boxStyle.boxClass.isEmpty()) {
        boxStyle.boxClass = "body";
    }
    if(id.isEmpty()) {
        id = generateId("image", boxStyle.boxClass);
    }
    QString text = "";
    if(mTokenizer.peekNext().mKind == Token::Kind::Text) {
        text = QString(mTokenizer.next().mText);
    }
    auto const imageBox = std::make_shared<ImageBox>(text, boxStyle, id, line);
    imageBox->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(imageBox);
}

void Parser::newTitle(int line){
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }
    QString id;
    auto boxStyle = readArguments(id);
    boxStyle.boxClass = "title";
    if(id.isEmpty()) {
        id = generateId("text", boxStyle.boxClass);
    }

    auto const frameId = mFrameList.vector.back()->id();
    QString text = frameId;
    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind == Token::Kind::Text && !nextToken.mText.isEmpty()) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<MarkdownTextBox>(text, boxStyle, id, line);
    textField->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(textField);
}

void Parser::newBody(int line){
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }
    QString id;
    auto boxStyle = readArguments(id);
    boxStyle.boxClass = "body";
    if(id.isEmpty()) {
        id = generateId("text", boxStyle.boxClass);
    }

    QString text;
    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind == Token::Kind::Text || nextToken.mKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<MarkdownTextBox>(text, boxStyle, id, line);
    textField->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(textField);
}

void Parser::newArrow(int line){
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }
    QString id;
    auto const boxStyle = readArguments(id);
    if(id.isEmpty()) {
        id = generateId("arrow", boxStyle.boxClass);
    }

    auto const arrow = std::make_shared<ArrowBox>(boxStyle, id, line);
    arrow->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(arrow);

    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind != Token::Kind::Command && nextToken.mKind != Token::Kind::EndOfFile){
        throw ParserError{"Expecting end of line", line};
        return;
    }
}

void Parser::newLine(int line){
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }

    QString id;
    auto const boxStyle = readArguments(id);
    if(id.isEmpty()) {
        id = generateId("line", boxStyle.boxClass);
    }

    auto const arrow = std::make_shared<LineBox>(boxStyle, id, line);
    arrow->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(arrow);

    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind != Token::Kind::Command && nextToken.mKind != Token::Kind::EndOfFile){
        throw ParserError{"Expecting end of line", line};
        return;
    }
}

void Parser::newPlainText(int line) {
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }

    QString id;
    auto boxStyle = readArguments(id);
    if(boxStyle.boxClass.isEmpty()) {
        boxStyle.boxClass = "body";
    }
    if(id.isEmpty()) {
        id = generateId("plaintext", boxStyle.boxClass);
    }

    QString text = "";
    auto const peekNextKind = mTokenizer.peekNext().mKind;
    auto const peeknext = mTokenizer.peekNext();
    if(peekNextKind == Token::Kind::Text || peekNextKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<PlainTextBox>(text, boxStyle, id, line);
    textField->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(textField);
}

void Parser::newCodeBox(int line) {
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }

    QString id;
    auto boxStyle = readArguments(id);
    if(boxStyle.boxClass.isEmpty()) {
        boxStyle.boxClass = "body";
    }
    if(!boxStyle.mFont.has_value()) {
        boxStyle.mFont = "Hack";
    }
    if(id.isEmpty()) {
        id = generateId("code", boxStyle.boxClass);
    }

    QString text = "";
    auto const peekNextKind = mTokenizer.peekNext().mKind;
    auto const peeknext = mTokenizer.peekNext();
    if(peekNextKind == Token::Kind::Text || peekNextKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<CodeBox>(text, boxStyle, id, line);
    textField->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(textField);
}

void Parser::newBlindText(int line) {
    if(mFrameList.empty()){
        throw ParserError{"Expecting \\frame", line};
        return;
    }

    QString id;
    auto boxStyle = readArguments(id);
    if(boxStyle.boxClass.isEmpty()) {
        boxStyle.boxClass = "body";
    }
    if(id.isEmpty()) {
        id = generateId("blindtext", boxStyle.boxClass);
    }


    QString text = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    auto const peekNext = mTokenizer.peekNext();
    if(peekNext.mKind == Token::Kind::Text) {
        auto lenght = peekNext.mText.toInt();
        text = text.left(lenght);
        mTokenizer.next();
    }
    auto const textField = std::make_shared<MarkdownTextBox>(text, boxStyle, id, line);
    textField->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(textField);
}

void Parser::setVariable(int line) {
    Token nextToken = mTokenizer.next();
    if(nextToken.mKind != Token::Kind::Text){
        throw ParserError{"Expecting variable value", line};
        return;
    }
    auto text = QString(nextToken.mText);
    auto list = text.split(QRegularExpression("\\s+"));
    auto variable = list[0];
    mVariables[addBracketsToVariable(variable)] = text.right(text.size() - variable.size() - 1);
}

void Parser::applyPause() {
    mPauseCount++;
    if(mTokenizer.peekNext().mKind != Token::Kind::Text && mTokenizer.peekNext().mKind != Token::Kind::MultiLineText) {
        return;
    }

    auto const lastTextBox = std::dynamic_pointer_cast<TextBox>(mFrameList.vector.back()->boxes().back());
    if(!lastTextBox) {
        return;
    }

    auto text = mTokenizer.next().mText;
    // Hack: need to be refractored
    text.insert(0, '\n');
    auto box = lastTextBox->clone();
    box->appendText(text);
    box->setPauseCounter(mPauseCount);
    mFrameList.vector.back()->appendBox(box);

    lastTextBox->setConfigId(lastTextBox->id());
    lastTextBox->setPauseMode(PauseDisplayMode::onlyInPause);
    lastTextBox->setId(generateId("text", lastTextBox->style().boxClass));
}

QString Parser::addBracketsToVariable(QString variable) const {
    return "%{" + variable + "}";
}

BoxStyle Parser::readArguments(QString &id) {
    BoxStyle boxStyle;
    auto argument = mTokenizer.peekNext();
    while(argument.mKind == Token::Kind::Argument){
        mTokenizer.next();
        auto argumentValue = mTokenizer.next();
        if(argumentValue.mKind != Token::Kind::ArgumentValue && !argumentValue.mText.isEmpty()){
            throw ParserError{"Expecting argument value", argument.mLine};
            return {};
        }
        if(argument.mText == "color"){
            QColor color;
            color.setNamedColor(QString(argumentValue.mText));
            boxStyle.mColor = color;
        }
        if(argument.mText == "opacity"){
            boxStyle.mOpacity = argumentValue.mText.toDouble();
        }
        if(argument.mText == "font-size"){
            boxStyle.mFontSize = argumentValue.mText.toInt();
        }
        if(argument.mText == "line-height"){
            if(argumentValue.mText.toDouble() != 0){
                boxStyle.mLineSpacing = argumentValue.mText.toDouble();
            }
        }
        if(argument.mText == "font-weight"){
            if(QString(argumentValue.mText) == "bold"){
                boxStyle.mFontWeight = FontWeight::bold;
            }
            else if(QString(argumentValue.mText) == "normal"){
                boxStyle.mFontWeight = FontWeight::normal;
            }
            else{
                throw ParserError{"Invalid value for 'font-weight' (possible values: bold, normal)", argumentValue.mLine};
            }
        }
        if(argument.mText == "font"){
            boxStyle.mFont = QString(argumentValue.mText);
        }
        if(argument.mText == "id"){
            id = QString(argumentValue.mText);
            if(id.startsWith("intern")) {
                throw ParserError{"User defined box IDs must not start with \"intern\"", argumentValue.mLine};
            }
            if(mBoxIds.find(id) != mBoxIds.end()) {
                throw ParserError{"Duplicate box ID", argumentValue.mLine};
            }
            mBoxIds.insert(id);
        }
        if(argument.mText == "left"){
            boxStyle.mGeometry.setLeft(argumentValue.mText.toInt());
            boxStyle.movable = false;
        }
        if(argument.mText == "top"){
            boxStyle.mGeometry.setTop(argumentValue.mText.toInt());
            boxStyle.movable = false;
        }
        if(argument.mText == "width"){
            boxStyle.mGeometry.setWidth(argumentValue.mText.toInt());
            boxStyle.movable = false;
        }
        if(argument.mText == "height"){
            boxStyle.mGeometry.setHeight(argumentValue.mText.toInt());
            boxStyle.movable = false;
        }
        if(argument.mText == "angle"){
            boxStyle.mGeometry.setAngle(argumentValue.mText.toDouble());
            boxStyle.movable = false;
        }
        if(argument.mText == "movable"){
            if(argumentValue.mText == "true") {
                boxStyle.movable = true;
            }
            else if(argumentValue.mText == "true") {
                boxStyle.movable = true;
            }
            else {
                throw ParserError{"Invalid value for 'movable' (possible values: true, false)", argumentValue.mLine};
            }
        }
        if(argument.mText == "text-align"){
            if(argumentValue.mText == "left") {
                boxStyle.mAlignment = Qt::AlignLeft;
            }
            else if(argumentValue.mText == "right") {
                boxStyle.mAlignment = Qt::AlignRight;
            }
            else if(argumentValue.mText == "center") {
                boxStyle.mAlignment = Qt::AlignCenter;
            }
            else if(argumentValue.mText == "justify") {
                boxStyle.mAlignment = Qt::AlignJustify;
            }
            else {
                throw ParserError{"Invalid value for 'text-align' (possible values: left, right, center, justify)", argumentValue.mLine};
            }
        }
        if(argument.mText == "class"){
            boxStyle.boxClass = argumentValue.mText;
        }
        if(argument.mText == "language"){
            boxStyle.language = QString(argumentValue.mText);
        }
        if(argument.mText == "background"){
            QColor color;
            color.setNamedColor(argumentValue.mText);
            if(!color.isValid()) {
                throw ParserError{"Invalid color", argumentValue.mLine};
            }
            boxStyle.mBackgroundColor = color;
        }
        if(argument.mText == "background-color"){
            QColor color;
            color.setNamedColor(argumentValue.mText);
            if(!color.isValid()) {
                throw ParserError{"Invalid color", argumentValue.mLine};
            }
            boxStyle.mBackgroundColor = color;
        }
        if(argument.mText == "border"){
            auto values = QString(argumentValue.mText).split(" ");
            if(values.empty()) {
                continue;
            }
            if(values[0].endsWith("px") && values.length() >= 2) {
                auto value = values[0];
                value.chop(2);
                bool ok;
                boxStyle.mBorder.width = value.toInt(&ok);
                if(!ok) {
                    throw ParserError{"Invalid width value for 'border'", argumentValue.mLine};
                }
                boxStyle.mBorder.style = values[1];
                if(values.length() >= 3) {
                    boxStyle.mBorder.color = QColor(QString(values[2]));
                }
            }
            else {
                boxStyle.mBorder.style = values[0];
                if(values.length() >= 2) {
                    boxStyle.mBorder.color = QColor(QString(values[1]));
                }
            }
        }

        argument = mTokenizer.peekNext();
    }
    return boxStyle;
}

QString Parser::generateId(QString type, QString boxclass) {
    auto const frameId = mFrameList.vector.back()->id();
    int boxCounter = 0;
    auto id = "intern-" + frameId + "-" + type + "-" + boxclass + "-0";
    while(mBoxIds.find(id) != mBoxIds.end()) {
        boxCounter++;
        id = "intern-" + frameId + "-" + type + "-" + boxclass + "-" + QString::number(boxCounter);
    }
    mBoxIds.insert(id);
    return id;
}

void Parser::setVariables(std::map<QString, QString> variables) {
    mVariables = variables;
}

std::map<QString, QString> Parser::Variables() const {
    return mVariables;
}
