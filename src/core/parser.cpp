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
            throw ParserError{"missing command", 0};
        }
        else{
            throw ParserError{"missing command", token.mLine};
        }
    }
    return mPreamble;
}

void Parser::preambleCommand(Token token) {
    if(token.mText == "\\usetemplate"){
        auto const nextToken = mTokenizer.next();
        if(nextToken.mKind != Token::Kind::Text) {
            throw ParserError{"Missing Template name", token.mLine};
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
            throw ParserError{"missing command", token.mLine};
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
    else if(token.mText == "\\blindtext"){
        newBlindText(token.mLine);
    }
    else if(token.mText == "\\setvar"){
        setVariable(token.mLine);
    }
    else{
        throw ParserError{"command does not exist", token.mLine};
    }
}

void Parser::newFrame(int line){
    mPauseCount = 0;
    auto token = mTokenizer.next();
    Box::List templateBoxes;
    QString frameClass;
    if(token.mKind == Token::Kind::Argument){
        if(token.mText != "class"){
            throw ParserError{"Only the Argument \"class\" is allowed after frame Command", token.mLine};
            return;
        }
        auto const tokenArgValue = mTokenizer.next();
        if(tokenArgValue.mKind != Token::Kind::ArgumentValue){
            throw ParserError{"Argment Value is missing", token.mLine};
            return;
        }
        frameClass = tokenArgValue.mText;
        token = mTokenizer.next();
    }
    if(token.mKind != Token::Kind::Text || token.mText.isEmpty()) {
        throw ParserError{"missing frame id", line};
        return;
    }
    auto const id = QString(token.mText);
    for(auto const& frame: mFrameList.vector) {
        if(frame->id() == id){
            throw ParserError{"frame id already exist", line};
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
        throw ParserError{"missing frame: type \\frame id", line};
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
        throw ParserError{"missing frame: type \\frame id", line};
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
        throw ParserError{"missing frame: type \\frame id", line};
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
        throw ParserError{"missing frame: type \\frame id", line};
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
        throw ParserError{"missing frame: type \\frame id", line};
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
        throw ParserError{"\\arrow command need no text", line};
        return;
    }
}

void Parser::newLine(int line){
    if(mFrameList.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
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
        throw ParserError{"\\line command need no text", line};
        return;
    }
}

void Parser::newPlainText(int line) {
    if(mFrameList.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }

    QString id;
    auto boxStyle = readArguments(id);
    if(boxStyle.boxClass.isEmpty()) {
        boxStyle.boxClass = "body";
    }
    if(id.isEmpty()) {
        id = generateId("arrow", boxStyle.boxClass);
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

void Parser::newBlindText(int line) {
    if(mFrameList.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }

    QString id;
    auto boxStyle = readArguments(id);
    if(boxStyle.boxClass.isEmpty()) {
        boxStyle.boxClass = "body";
    }
    if(id.isEmpty()) {
        id = generateId("arrow", boxStyle.boxClass);
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
        throw ParserError{"Missing Variable declaration", line};
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
    box->setPauseMode(PauseDisplayMode::onlyInPause);
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
            throw ParserError{"Missing Value in argument", argument.mLine};
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
                throw ParserError{"font-weight can only be bold or normal", argumentValue.mLine};
            }
        }
        if(argument.mText == "font"){
            boxStyle.mFont = QString(argumentValue.mText);
        }
        if(argument.mText == "id"){
            id = QString(argumentValue.mText);
            if(id.startsWith("intern")) {
                throw ParserError{"User defined Box Ids should not start with \"intern\"", argumentValue.mLine};
            }
            if(mBoxIds.find(id) != mBoxIds.end()) {
                throw ParserError{"Box Id already exists", argumentValue.mLine};
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
                throw ParserError{"movable: expect true or false", argumentValue.mLine};
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
                throw ParserError{"possible alignment: left, right, center, justify", argumentValue.mLine};
            }
        }
        if(argument.mText == "class"){
            boxStyle.boxClass = argumentValue.mText;
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
