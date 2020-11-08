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


std::vector<std::shared_ptr<Frame>> Parser::readJson(QString text, ConfigBoxes* configuration)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &error);
    qWarning() << error.errorString();
    std::vector<std::shared_ptr<Frame>> frames;

    QJsonArray root = doc.array();
    qWarning() << "Size" << root.size();
    for (int i = 0; i < root.size(); i++) {
        std::vector<std::shared_ptr<Box>> boxes;
        QJsonArray frame = root.at(i).toArray();
        qWarning() << "Hallo" << i;

        for (int j = 0; j < frame.size(); j++){
            auto const box = frame.at(j).toObject();
            auto const type = box.value("type").toString();
            auto idNumber = box.value("id").toInt();
            if (type == "text"){
                auto const text = box.value("text").toString();
                QRect rect;
                if(!configuration->getRect(idNumber).isEmpty()){
                    rect = configuration->getRect(idNumber);
                } else {
                    rect = QRect(25, 25, 750, 50);
                }
                auto const newTitle = std::make_shared<TextField>(text, rect, idNumber);
                newTitle->setMovable(box.value("movable").toBool(true));
                boxes.push_back(newTitle);
            }
            else if (type == "image"){
                auto const Imagefile = box.value("file").toString();
                QRect rect;
                if(!configuration->getRect(idNumber).isEmpty()){
                    rect = configuration->getRect(idNumber);
                } else {
                    rect = QRect(25, 75, 750, 300);
                }
                auto const newImage = std::make_shared<Picture>(Imagefile, rect, idNumber);
                boxes.push_back(newImage);
            }
        }
        auto newFrame = std::make_shared<Frame>();
        newFrame->setBoxes(boxes);
        frames.push_back(newFrame);
    }
    return frames;
}
