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

std::vector<std::shared_ptr<Frame>> Parser::readJson(QString text)
{
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());

//    QJsonObject values = doc.object();
//    QJsonValue aspectRatio = values.value("aspectRatio");

    std::vector<std::shared_ptr<Frame>> frames;
    QJsonArray root = doc.array();
    for (int i = 0; i < root.size(); i++) {
        QJsonObject frame = root.at(i).toObject();

        auto const title = frame.value("title").toObject();
        auto const text = title.value("text").toString();
        auto idNumber = title.value("id").toInt();
        auto const newTitle = std::make_shared<TextField>(text, QRect(25, 25, 750, 50), idNumber);
        newTitle->setMovable(title.value("movable").toBool(true));

        auto const body = frame.value("body").toObject();
        auto const bodyText = body.value("text").toString();
        idNumber = body.value("id").toInt();
        auto const newText = std::make_shared<TextField>(bodyText, QRect(25, 75, 750, 300), idNumber);

        auto const image = frame.value("image").toObject();
        auto const Imagefile = image.value("file").toString();
        idNumber = image.value("id").toInt();
        auto const newImage = std::make_shared<Picture>(Imagefile, QRect(25, 75, 750, 300), idNumber);

//        QJsonValue imageName = frame.value("image");
//        auto newImage = std::make_shared<Picture>(imageName.toString(), QRect(25, 75, 750, 300), 1);

        std::vector<std::shared_ptr<Box>> boxes{newTitle, newText, newImage};
        auto newFrame = std::make_shared<Frame>();
        newFrame->setBoxes(boxes);
        frames.push_back(newFrame);
    }
    return frames;
}

std::vector<std::shared_ptr<Frame>> Parser::readJson(QString text, std::vector<std::shared_ptr<Frame>> frames)
{
//        QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());

//        std::vector<std::shared_ptr<Frame>> newFrames;
//        QJsonArray root = doc.array();
//        for (int i = 0; i < root.size(); i++) {
//            QJsonObject frame = root.at(i).toObject();

//        }
    return frames;

}
