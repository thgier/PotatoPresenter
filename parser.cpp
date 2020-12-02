#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

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


std::optional<FrameList> Parser::readJson(QString text, ConfigBoxes* configuration)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &error);
    qWarning() << error.errorString();
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
            auto idNumber = box.value("id").toInt();
            if (type == "text"){
                auto const text = box.value("text").toString();
                QRect rect;
                if(configuration->getRect(idNumber).isEmpty()){
                    rect = QRect(50, 200, 1500, 650);
                } else {
                    rect = configuration->getRect(idNumber);
                }
                auto const newText = std::make_shared<TextField>(text, rect, idNumber);
                newText->setMovable(box.value("movable").toBool(true));
                boxes.push_back(newText);
            }
            else if (type == "image"){
                auto const Imagefile = box.value("file").toString();
                QRect rect;
                if(configuration->getRect(idNumber).isEmpty()){
                    rect = QRect(50, 200, 1500, 650);
                } else {
                    rect = configuration->getRect(idNumber);
                }
                auto const newImage = std::make_shared<Picture>(Imagefile, rect, idNumber);
                boxes.push_back(newImage);
            }
        }
        auto newFrame = std::make_shared<Frame>(frameId);
        newFrame->setBoxes(boxes);
        frames.push_back(newFrame);
    }
    return frames;
}
