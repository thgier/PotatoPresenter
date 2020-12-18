#include "configboxes.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>

ConfigBoxes::ConfigBoxes()
{

}

void ConfigBoxes::loadConfigurationFile(QString filename){
    mFilename = filename;
    QFile file(mFilename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    auto const val = file.readAll();
    qDebug() << val;
    auto doc = QJsonDocument::fromJson(val);
    loadConfigFromJson(doc);
}

void ConfigBoxes::saveJsonConfigurations(QJsonObject &json, const configurations config){
    QJsonObject jsonRect;
    auto const boxrect = config.rect;
    jsonRect["xPosition"] = boxrect.rect().left();
    jsonRect["yPosition"] = boxrect.rect().top();
    jsonRect["width"] = boxrect.rect().width();
    jsonRect["height"] = boxrect.rect().height();
    jsonRect["angle"] = boxrect.angle();
    json["rect"] = jsonRect;

}

configurations ConfigBoxes::readJsonConfigurations(const QJsonObject &json){
    auto const rect = json.value("rect").toObject();
    auto const x = rect["xPosition"].toInt();
    auto const y = rect["yPosition"].toInt();
    auto const width = rect["width"].toInt();
    auto const height = rect["height"].toInt();
    auto const angle = rect["angle"].toDouble();
    configurations newConfig;
    newConfig.rect = BoxRect(QRect(x, y, width, height), angle);
    return newConfig;
}

void ConfigBoxes::loadConfigFromJson(QJsonDocument doc){
    QJsonArray root = doc.array();
    for (int i = 0; i < root.size(); i++) {
        QJsonObject configBox = root.at(i).toObject();
        auto const id = configBox.value("id").toString();
        auto const newConfig = readJsonConfigurations(configBox);
        mConfigMap[id] = newConfig;
    }
}

void ConfigBoxes::saveConfig()
{
    QFile file(mFilename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open output file" << mFilename << ":" << file.error();
        return;
    }
    QJsonArray array;
    for(auto it = mConfigMap.begin(); it != mConfigMap.end(); it++){
        QJsonObject item;
        item["id"] = it->first;
        saveJsonConfigurations(item, it->second);
        array.append(item);
    }
    auto doc = QJsonDocument(array);
    file.write(doc.toJson());
}

void ConfigBoxes::addRect(BoxRect rect, QString id) {
    configurations newConfig;
    newConfig.rect = rect;
    mConfigMap[id] = newConfig;
    saveConfig();
}

BoxRect ConfigBoxes::getRect(QString id){
    if(auto it = mConfigMap.find(id); it != mConfigMap.end()){
        return it->second.rect;
    }
    return {};
}
