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
#include "textbox.h"
#include "arrowbox.h"

Parser::Parser()
{
    mLayout = std::make_shared<Layout>();
}

void Parser::loadInput(QIODevice *input, ConfigBoxes *configuration){
    mTokenizer.loadInput(input);
    mConfigBoxes = configuration;
}

void Parser::loadInput(QByteArray input, ConfigBoxes *configuration){
    mTokenizer.loadInput(input);
    mConfigBoxes = configuration;
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
    return mFrames;
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
    else if(token.mText == "\\title"){
        newTitle(token.mLine);
    }
    else if(token.mText == "\\arrow"){
        newArrow(token.mLine);
    }
    else if(token.mText == "\\setvar"){
        setVariable(token.mLine);
    }
    else if(token.mText == "\\usetemplate"){
        loadTemplate(token.mLine);
    }
    else{
        throw ParserError{"command does not exist", token.mLine};
    }
}

void Parser::newFrame(int line){
    mBoxCounter = 0;
    auto token = mTokenizer.peekNext();
    Box::List templateBoxes;
    if(token.mKind == Token::Kind::Argument){
        if(token.mText != "template"){
            throw ParserError{"Only the Argument \"template\" is allowed after frame Command", token.mLine};
            return;
        }
        mTokenizer.next();
        auto const tokenArgValue = mTokenizer.next();
        if(tokenArgValue.mKind != Token::Kind::ArgumentValue){
            throw ParserError{"Argment Value is missing", token.mLine};
            return;
        }
        if(mTemplate){
            templateBoxes = mTemplate->getTemplateSlide(tokenArgValue.mText);
        }
        token = mTokenizer.peekNext();
    }
    else{
        if(mTemplate){
            templateBoxes = mTemplate->getTemplateSlide("default");
        }
    }
    if(token.mKind != Token::Kind::Text || token.mText.isEmpty()) {
        throw ParserError{"missing frame id", line};
        return;
    }
    auto const id = QString(mTokenizer.next().mText);
    for(auto const& frame: mFrames) {
        if(frame->id() == id){
            throw ParserError{"frame id already exist", line};
        }
    }
    mFrames.push_back(std::make_shared<Frame>(id));
    mFrames.back()->setTemplateBoxes(templateBoxes);
}

void Parser::newTextField(int line){
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }
    auto id = generateId();
    auto const boxStyle = readArguments(id, "Body");

    QString text = "";
    auto const peekNextKind = mTokenizer.peekNext().mKind;
    auto const peeknext = mTokenizer.peekNext();
    if(peekNextKind == Token::Kind::Text || peekNextKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<TextBox>(text, getRect(id), id);
    textField->setBoxStyle(boxStyle);
    textField->setVariables(mVariables);
    mBoxCounter++;
    mFrames.back()->appendBox(textField);
}

void Parser::newImage(int line) {
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }
    auto id = generateId();
    auto const boxStyle = readArguments(id, "Body");

    QString text = "";
    if(mTokenizer.peekNext().mKind == Token::Kind::Text) {
        text = QString(mTokenizer.next().mText);
    }
    auto const imageBox = std::make_shared<ImageBox>(text, getRect(id), id);
    imageBox->setVariables(mVariables);
    imageBox->setBoxStyle(boxStyle);
    mBoxCounter++;
    mFrames.back()->appendBox(imageBox);
}

void Parser::newTitle(int line){
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }
    auto id = generateId();
    auto const boxStyle = readArguments(id, "Title");

    auto const frameId = mFrames.back()->id();
    QString text = frameId;
    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind == Token::Kind::Text && !nextToken.mText.isEmpty()) {
        text = QString(mTokenizer.next().mText);
    }
    auto rect = mConfigBoxes->getRect(id);
    if(rect.isEmpty()){
        rect = mLayout->mTitlePos;
    }
    auto const textField = std::make_shared<TextBox>(text, rect, id);
    textField->setBoxStyle(boxStyle);
    textField->setVariables(mVariables);
    mBoxCounter++;
    mFrames.back()->appendBox(textField);
}

void Parser::newArrow(int line){
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }
    auto id = generateId();
    auto const boxStyle = readArguments(id, "Body");

    auto rect = mConfigBoxes->getRect(id);
    if(rect.isEmpty()){
        rect = mLayout->mArrowPos;
    }
    auto const arrow = std::make_shared<ArrowBox>(rect, id);
    arrow->setBoxStyle(boxStyle);
    mFrames.back()->appendBox(arrow);
    mBoxCounter++;

    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind != Token::Kind::Command && nextToken.mKind != Token::Kind::EndOfFile){
        throw ParserError{"\\arrow command need no text", line};
        return;
    }
}

void Parser::setVariable(int line){
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

QString Parser::addBracketsToVariable(QString variable) const{
    return "%{" + variable + "}";
}

BoxGeometry const Parser::getRect(QString id) {
    auto rect = mConfigBoxes->getRect(id);
    if(rect.isEmpty()){
        rect = mLayout->mBodyPos;
        switch (mBoxCounter) {
        case 0:
            rect = mLayout->mTitlePos;
            break;
        case 1:
            rect = mLayout->mBodyPos;
            break;
        case 2:
            auto const lastBox = mFrames.back()->getBoxes().back();
            if(mConfigBoxes->getRect(lastBox->id()).isEmpty()) {
                lastBox->setRect(mLayout->mLeftPos);
                rect = mLayout->mRightPos;
            }
            break;
        }
    }
    return rect;
}

BoxStyle Parser::readArguments(QString &id, QString BoxStyleIdentifier){
    BoxStyle boxStyle;
    if(mTemplate){
        boxStyle = mTemplate->getStyle(BoxStyleIdentifier);
    }
    auto argument = mTokenizer.peekNext();
    while(argument.mKind == Token::Kind::Argument){
        mTokenizer.next();
        auto argumentValue = mTokenizer.next();
        if(argumentValue.mKind != Token::Kind::ArgumentValue){
            throw ParserError{"Missing Value in argument", argument.mLine};
            return boxStyle;
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
        if(argument.mText == "font"){
            boxStyle.mFont = QString(argumentValue.mText);
        }
        if(argument.mText == "id"){
            id = QString(argumentValue.mText);
            if(std::any_of(mUserIds.begin(), mUserIds.end(), [id](auto a){return a == id;})){
                throw ParserError{"Id already exists", argumentValue.mLine};
            }
            mUserIds.push_back(id);
        }
        argument = mTokenizer.peekNext();
    }
    return boxStyle;
}

void Parser::loadTemplate(int line){
    if(mParsingTemplate){
        throw ParserError{"Cannot use a Template in a Template", line};
        return;
    }
    auto token = mTokenizer.next();
    if(token.mKind != Token::Kind::Text){
        throw ParserError{"Missing Template File", line};
    }
    mTemplate = std::make_shared<Template>();

    try {
        mTemplate->readTemplateConfig(token.mText + ".json");
    }  catch (ConfigError& error) {
        throw ParserError{error.errorMessage, line};
    }

    auto file = QFile(token.mText + ".txt");
    if(!file.open(QIODevice::ReadOnly)){
        throw ParserError{"Can't open file" + file.fileName(), line};
        return;
    }

    Parser parser;
    parser.setFileIsATemplate(true);
    parser.setVariables(mVariables);
    parser.loadInput(file.readAll(), &mTemplate->Configuration());
    mTemplate->setFrames(parser.readInput());
    mLayout = mTemplate->getLayout();
}


QString Parser::generateId(){
    auto const frameId = mFrames.back()->id();
    auto id = frameId + "-intern-" + QString::number(mBoxCounter);
    return id;
}

void Parser::setFileIsATemplate(bool fileIsATemplate){
    mParsingTemplate = fileIsATemplate;
}

void Parser::setVariables(std::map<QString, QString> variables){
    mVariables = variables;
}
