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
    auto const rect = config.rect;
    jsonRect["xPosition"] = rect.left();
    jsonRect["yPosition"] = rect.top();
    jsonRect["width"] = rect.width();
    jsonRect["height"] = rect.height();
    json["rect"] = jsonRect;

}

configurations ConfigBoxes::readJsonConfigurations(const QJsonObject &json){
    auto const rect = json.value("rect").toObject();
    auto const x = rect["xPosition"].toInt();
    auto const y = rect["yPosition"].toInt();
    auto const width = rect["width"].toInt();
    auto const height = rect["height"].toInt();
    configurations newConfig;
    newConfig.rect = QRect(x, y, width, height);
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

void ConfigBoxes::addRect(QRect rect, QString id) {
    configurations newConfig;
    newConfig.rect = rect;
    mConfigMap[id] = newConfig;
    saveConfig();
}

QRect ConfigBoxes::getRect(QString id){
    if(auto it = mConfigMap.find(id); it != mConfigMap.end()){
        return it->second.rect;
    }
    return {};
}
