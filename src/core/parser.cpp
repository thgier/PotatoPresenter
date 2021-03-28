/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

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
#include "slide.h"
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
    while(!(mTokenizer.peekNext().mKind == Token::Kind::Command && mTokenizer.peekNext().mText == "\\slide")
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

SlideList Parser::readInput(){
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
    for(auto const& slide: mSlideList.vector){
        slide->setVariable("%{totalpages}", QString::number(mSlideList.vector.size() - 1));
    }
    return mSlideList;
}

void Parser::command(Token token){
    if(token.mText == "\\slide"){
        newSlide(token.mLine);
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

void Parser::newSlide(int line){
    mPauseCount = 0;
    auto token = mTokenizer.next();
    QString slideClass;
    if(token.mKind == Token::Kind::Argument){
        if(token.mText != "class"){
            throw ParserError{QString("Invalid argument '%1' for \\slide").arg(QString(token.mText)), token.mLine};
            return;
        }
        auto const tokenArgValue = mTokenizer.next();
        if(tokenArgValue.mKind != Token::Kind::ArgumentValue){
            throw ParserError{"Missing value for argument", token.mLine};
            return;
        }
        slideClass = tokenArgValue.mText;
        token = mTokenizer.next();
    }
    if(token.mKind != Token::Kind::Text || token.mText.isEmpty()) {
        throw ParserError{"Expecting slide id", line};
        return;
    }
    auto const id = QString(token.mText);
    for(auto const& slide: mSlideList.vector) {
        if(slide->id() == id){
            throw ParserError{QString("Duplicate slide ID '%1'").arg(id), line};
        }
    }
    mVariables["%{pagenumber}"] = QString::number(mSlideList.vector.size());
    if(mVariables.find("%{date}") == mVariables.end()){
        mVariables["%{date}"] = QDate::currentDate().toString();
    }
    if(mVariables.find("%{resourcepath}") == mVariables.end()){
        mVariables["%{resourcepath}"] = mResourcepath;
    }
    mSlideList.vector.push_back(std::make_shared<Slide>(id, mVariables, line));
    mSlideList.vector.back()->setSlideClass(slideClass);
}

void Parser::newTextField(int line){
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
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
    mSlideList.vector.back()->appendBox(textField);
}

void Parser::newImage(int line) {
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
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
    mSlideList.vector.back()->appendBox(imageBox);
}

void Parser::newTitle(int line){
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
        return;
    }
    QString id;
    auto boxStyle = readArguments(id);
    boxStyle.boxClass = "title";
    if(id.isEmpty()) {
        id = generateId("text", boxStyle.boxClass);
    }

    auto const slideId = mSlideList.vector.back()->id();
    QString text = slideId;
    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind == Token::Kind::Text && !nextToken.mText.isEmpty()) {
        text = QString(mTokenizer.next().mText);
    }
    auto const textField = std::make_shared<MarkdownTextBox>(text, boxStyle, id, line);
    textField->setPauseCounter(mPauseCount);
    mSlideList.vector.back()->appendBox(textField);
}

void Parser::newBody(int line){
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
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
    mSlideList.vector.back()->appendBox(textField);
}

void Parser::newArrow(int line){
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
        return;
    }
    QString id;
    auto const boxStyle = readArguments(id);
    if(id.isEmpty()) {
        id = generateId("arrow", boxStyle.boxClass);
    }

    auto const arrow = std::make_shared<ArrowBox>(boxStyle, id, line);
    arrow->setPauseCounter(mPauseCount);
    mSlideList.vector.back()->appendBox(arrow);

    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind != Token::Kind::Command && nextToken.mKind != Token::Kind::EndOfFile){
        throw ParserError{"Expecting end of line", line};
        return;
    }
}

void Parser::newLine(int line){
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
        return;
    }

    QString id;
    auto const boxStyle = readArguments(id);
    if(id.isEmpty()) {
        id = generateId("line", boxStyle.boxClass);
    }

    auto const arrow = std::make_shared<LineBox>(boxStyle, id, line);
    arrow->setPauseCounter(mPauseCount);
    mSlideList.vector.back()->appendBox(arrow);

    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind != Token::Kind::Command && nextToken.mKind != Token::Kind::EndOfFile){
        throw ParserError{"Expecting end of line", line};
        return;
    }
}

void Parser::newPlainText(int line) {
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
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
    mSlideList.vector.back()->appendBox(textField);
}

void Parser::newCodeBox(int line) {
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
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
    mSlideList.vector.back()->appendBox(textField);
}

void Parser::newBlindText(int line) {
    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
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
    mSlideList.vector.back()->appendBox(textField);
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

    auto const lastTextBox = std::dynamic_pointer_cast<TextBox>(mSlideList.vector.back()->boxes().back());
    if(!lastTextBox) {
        return;
    }

    auto text = mTokenizer.next().mText;
    // Hack: need to be refractored
    text.insert(0, '\n');
    auto box = lastTextBox->clone();
    box->appendText(text);
    box->setPauseCounter(mPauseCount);
    mSlideList.vector.back()->appendBox(box);

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
        bool numberOk = true;
        mTokenizer.next();
        auto argumentValue = mTokenizer.next();
        if(argumentValue.mKind != Token::Kind::ArgumentValue && !argumentValue.mText.isEmpty()){
            throw ParserError{"Expecting argument value", argument.mLine};
            return {};
        }
        else if(argument.mText == "color"){
            QColor color;
            color.setNamedColor(QString(argumentValue.mText));
            if(!color.isValid()) {
                throw ParserError{QString("Invalid color '%1'").arg(QString(argumentValue.mText)), argumentValue.mLine};
            }
            boxStyle.mColor = color;
        }
        else if(argument.mText == "opacity"){
            boxStyle.mOpacity = argumentValue.mText.toDouble(&numberOk);
        }
        else if(argument.mText == "font-size"){
            boxStyle.mFontSize = argumentValue.mText.toInt(&numberOk);
        }
        else if(argument.mText == "line-height"){
            if(argumentValue.mText.toDouble() != 0){
                boxStyle.mLineSpacing = argumentValue.mText.toDouble(&numberOk);
            }
        }
        else if(argument.mText == "font-weight"){
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
        else if(argument.mText == "font"){
            boxStyle.mFont = QString(argumentValue.mText);
        }
        else if(argument.mText == "id"){
            id = QString(argumentValue.mText);
            if(id.startsWith("intern")) {
                throw ParserError{"User defined box IDs must not start with \"intern\"", argumentValue.mLine};
            }
            if(mBoxIds.find(id) != mBoxIds.end()) {
                throw ParserError{"Duplicate box ID", argumentValue.mLine};
            }
            mBoxIds.insert(id);
        }
        else if(argument.mText == "left"){
            boxStyle.mGeometry.setLeft(argumentValue.mText.toInt(&numberOk));
            boxStyle.movable = false;
        }
        else if(argument.mText == "top"){
            boxStyle.mGeometry.setTop(argumentValue.mText.toInt(&numberOk));
            boxStyle.movable = false;
        }
        else if(argument.mText == "width"){
            boxStyle.mGeometry.setWidth(argumentValue.mText.toInt(&numberOk));
            boxStyle.movable = false;
        }
        else if(argument.mText == "height"){
            boxStyle.mGeometry.setHeight(argumentValue.mText.toInt(&numberOk));
            boxStyle.movable = false;
        }
        else if(argument.mText == "angle"){
            boxStyle.mGeometry.setAngle(argumentValue.mText.toDouble(&numberOk));
            boxStyle.movable = false;
        }
        else if(argument.mText == "movable"){
            if(argumentValue.mText == "true") {
                boxStyle.movable = true;
            }
            else if(argumentValue.mText == "false") {
                boxStyle.movable = false;
            }
            else {
                throw ParserError{"Invalid value for 'movable' (possible values: true, false)", argumentValue.mLine};
            }
        }
        else if(argument.mText == "text-align"){
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
        else if(argument.mText == "class"){
            boxStyle.boxClass = argumentValue.mText;
        }
        else if(argument.mText == "language"){
            boxStyle.language = QString(argumentValue.mText);
        }
        else if(argument.mText == "background"){
            QColor color;
            color.setNamedColor(argumentValue.mText);
            if(!color.isValid()) {
                throw ParserError{"Invalid color", argumentValue.mLine};
            }
            boxStyle.mBackgroundColor = color;
        }
        else if(argument.mText == "background-color"){
            QColor color;
            color.setNamedColor(argumentValue.mText);
            if(!color.isValid()) {
                throw ParserError{"Invalid color", argumentValue.mLine};
            }
            boxStyle.mBackgroundColor = color;
        }
        else if(argument.mText == "padding") {
            boxStyle.mPadding = argumentValue.mText.toInt(&numberOk);
        }
        else if(argument.mText == "border"){
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
        else {
            throw ParserError{QString("Invalid Argument '%1'").arg(QString(argument.mText)), argument.mLine};
        }
        if(!numberOk) {
            throw ParserError{"Invalid number", argumentValue.mLine};
        }

        argument = mTokenizer.peekNext();
    }
    return boxStyle;
}

QString Parser::generateId(QString type, QString boxclass) {
    auto const slideId = mSlideList.vector.back()->id();
    int boxCounter = 0;
    auto id = "intern-" + slideId + "-" + type + "-" + boxclass + "-0";
    while(mBoxIds.find(id) != mBoxIds.end()) {
        boxCounter++;
        id = "intern-" + slideId + "-" + type + "-" + boxclass + "-" + QString::number(boxCounter);
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
