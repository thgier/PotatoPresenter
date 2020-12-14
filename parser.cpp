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
            command(token.mText);
        }
        else{
        }
        token = mTokenizer.next();
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
    mBoxCounter = 0;
    auto const token = mTokenizer.peekNext();
    if(token.mKind != Token::Kind::Text || token.mText.isEmpty()) {
        return;
    }
    mFrames.push_back(std::make_shared<Frame>(QString(mTokenizer.next().mText)));
}

void Parser::newTextField(){
    if(mFrames.empty()){
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

void Parser::newImage() {
    if(mFrames.empty()){
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
