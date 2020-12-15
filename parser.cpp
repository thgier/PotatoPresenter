#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QCryptographicHash>
#include <charconv>

#include "parser.h"
#include "frame.h"
#include "box.h"
#include "picture.h"
#include "textfield.h"

Parser::Parser()
    : mLayout(aspectRatio::sixteenToNine)
{
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
    else{
        throw ParserError{"command does not exist", token.mLine};
    }
}

void Parser::newFrame(int line){
    mBoxCounter = 0;
    auto const token = mTokenizer.peekNext();
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
}

void Parser::newTextField(int line){
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \\frame id", line};
        return;
    }
    QString text = "";
    auto const peekNextKind = mTokenizer.peekNext().mKind;
    auto const peeknext =mTokenizer.peekNext();
    if(peekNextKind == Token::Kind::Text || peekNextKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const id = mFrames.back()->id() + "-" + QString::number(mBoxCounter);
    auto const textField = std::make_shared<TextField>(text, getRect(id), id);
    mBoxCounter++;
    mFrames.back()->appendBox(textField);
}

void Parser::newImage(int line) {
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \frame id", line};
        return;
    }
    QString text = "";
    if(mTokenizer.peekNext().mKind == Token::Kind::Text) {
        text = QString(mTokenizer.next().mText);
    }
    auto const id = mFrames.back()->id() + "-" + QString::number(mBoxCounter);
    auto const textField = std::make_shared<Picture>(text, getRect(id), id);
    mBoxCounter++;
    mFrames.back()->appendBox(textField);
}

void Parser::newTitle(int line){
    if(mFrames.empty()){
        throw ParserError{"missing frame: type \frame id", line};
        return;
    }
    auto const frameId = mFrames.back()->id();
    QString text = frameId;
    auto const nextToken = mTokenizer.peekNext();
    if(nextToken.mKind == Token::Kind::Text && !nextToken.mText.isEmpty()) {
        text = QString(mTokenizer.next().mText);
    }
    auto const id = frameId + "-" + QString::number(mBoxCounter);
    auto rect = mConfigBoxes->getRect(id);
    if(rect.isEmpty()){
        rect = mLayout.mTitlePos;
    }
    auto const textField = std::make_shared<TextField>(text, rect, id);
    mBoxCounter++;
    mFrames.back()->appendBox(textField);
}

QRect const Parser::getRect(QString id) {
    auto rect = mConfigBoxes->getRect(id);
    if(rect.isEmpty()){
        rect = mLayout.mBodyPos;
        switch (mBoxCounter) {
        case 0:
            rect = mLayout.mTitlePos;
            break;
        case 1:
            rect = mLayout.mBodyPos;
            break;
        case 2:
            auto const idPrevious = mFrames.back()->id() + "-1";
            if(mConfigBoxes->getRect(idPrevious).isEmpty()) {
                mFrames.back()->getBoxes()[1]->setRect(mLayout.mLeftPos);
                rect = mLayout.mRightPos;
            }
            break;
        }
    }
    return rect;
}
