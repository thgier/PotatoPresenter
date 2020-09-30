#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "parser.h"
#include "frame.h"
#include "box.h"
#include "titlefield.h"
#include "bigtextfield.h"

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
        QJsonValue title = frame.value("title");
        auto newTitle = std::make_shared<TextField>(title.toString(), QRect(25, 25, 750, 50));
        QJsonValue content = frame.value("text");
        qInfo() << content;
        auto newText = std::make_shared<TextField>(content.toString(), QRect(25, 75, 750, 300));
//        std::vector<std::shared_ptr<Box>> boxes{newText};
        std::vector<std::shared_ptr<Box>> boxes{newTitle, newText};
        auto newFrame = std::make_shared<Frame>();
        newFrame->setBoxes(boxes);
        frames.push_back(newFrame);
    }
    return frames;
}

