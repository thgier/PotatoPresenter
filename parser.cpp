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

enum nineToSechsteen: int {
    titlet = 1,

};


Parser::Parser()
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
            command(token.mText);
        }
        else{
        }
        token = mTokenizer.next();
    }
    if(mCurrentFrame != nullptr){
        mFrames.push_back(mCurrentFrame);
    }
    return mFrames;
}

void Parser::command(QByteArray text){
    if(text == "\\frame"){
        newFrame();
    }
    else if(text == "\\text"){
        newTextField();
    }
    else if(text == "\\image"){
        newImage();
    }
}

void Parser::newFrame(){
    if(mCurrentFrame != nullptr){
        mFrames.push_back(mCurrentFrame);
        mBoxCounter = 0;
    }
    auto const token = mTokenizer.peekNext();
    if(token.mKind != Token::Kind::Text || token.mText.isEmpty()) {
        return;
    }
    mCurrentFrame = std::make_shared<Frame>(QString(mTokenizer.next().mText));
}

void Parser::newTextField(){
    if(mCurrentFrame == nullptr){
        return;
    }
    QString text = "";
    auto const peekNextKind = mTokenizer.peekNext().mKind;
    auto const peeknext =mTokenizer.peekNext();
    if(peekNextKind == Token::Kind::Text || peekNextKind == Token::Kind::MultiLineText) {
        text = QString(mTokenizer.next().mText);
    }
    auto const id = mCurrentFrame->id() + "-" + QString::number(mBoxCounter);
    auto const textField = std::make_shared<TextField>(text, getRect(id), id);
    mBoxCounter++;
    mCurrentFrame->appendBox(textField);
}

void Parser::newImage() {
    if(mCurrentFrame == nullptr){
        return;
    }
    QString text = "";
    if(mTokenizer.peekNext().mKind == Token::Kind::Text) {
        text = QString(mTokenizer.next().mText);
    }
    auto const id = mCurrentFrame->id() + "-" + QString::number(mBoxCounter);
    auto const textField = std::make_shared<Picture>(text, getRect(id), id);
    mBoxCounter++;
    mCurrentFrame->appendBox(textField);
}

QRect const Parser::getRect(QString id) {
    auto rect = mConfigBoxes->getRect(id);
    if(rect.isEmpty()){
        rect = QRect(50, 200, 1500, 650);
    }
    return rect;
}


std::optional<FrameList> Parser::readJson(QString text, ConfigBoxes* configuration)
{
    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(text.toUtf8(), &error);
    if(error.error != QJsonParseError::NoError){
        return {};
    }
    FrameList frames;

    QJsonArray root = doc.array();
    qWarning() << "Size" << root.size();
    for (int i = 0; i < root.size(); i++) {
        QJsonObject frameStart = root.at(i).toObject();
        auto const frameId = frameStart.value("frame").toString();
        std::vector<std::shared_ptr<Box>> boxes;
        QJsonArray frame = frameStart.value("content").toArray();

        for (int j = 0; j < frame.size(); j++){
            auto const box = frame.at(j).toObject();
            auto const type = box.value("type").toString();
//            auto idNumber = box.value("id").toInt();
            auto id = frameId;
            id += "-" + QString::number(j);
            if (type == "text"){
                auto const text = box.value("text").toString();
                QRect rect;
                if(configuration->getRect(id).isEmpty()){
                    rect = QRect(50, 200, 1500, 650);
                } else {
                    rect = configuration->getRect(id);
                }
                auto const newText = std::make_shared<TextField>(text, rect, id);
                newText->setMovable(box.value("movable").toBool(true));
                boxes.push_back(newText);
            }
            else if (type == "image"){
                auto const Imagefile = box.value("file").toString();
                QRect rect;
                if(configuration->getRect(id).isEmpty()){
                    rect = QRect(50, 200, 1500, 650);
                } else {
                    rect = configuration->getRect(id);
                }
                auto const newImage = std::make_shared<Picture>(Imagefile, rect, id);
                boxes.push_back(newImage);
            }
        }
        auto newFrame = std::make_shared<Frame>(frameId);
        newFrame->setBoxes(boxes);
        frames.push_back(newFrame);
    }
    return frames;
}
