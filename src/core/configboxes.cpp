#include "configboxes.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>

ConfigBoxes::ConfigBoxes()
{

}

void ConfigBoxes::loadConfigurationFile(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw ConfigError{"Cannot open file", filename};
        return;
    }
    auto const val = file.readAll();
    auto doc = QJsonDocument::fromJson(val);
    loadConfigFromJson(doc);
    file.close();
    mPath = filename;
}

void ConfigBoxes::saveJsonConfigurations(QJsonObject &json, const JsonConfig config){
    QJsonObject jsonRect;
    auto const boxrect = config.geometry;
    jsonRect["xPosition"] = boxrect.rect.left();
    jsonRect["yPosition"] = boxrect.rect.top();
    jsonRect["width"] = boxrect.rect.width();
    jsonRect["height"] = boxrect.rect.height();
    jsonRect["angle"] = boxrect.angle;
    json["rect"] = jsonRect;

}

JsonConfig ConfigBoxes::readJsonConfigurations(const QJsonObject &json){
    auto const rect = json.value("rect").toObject();
    auto const x = rect["xPosition"].toInt();
    auto const y = rect["yPosition"].toInt();
    auto const width = rect["width"].toInt();
    auto const height = rect["height"].toInt();
    auto const angle = rect["angle"].toDouble();
    JsonConfig newConfig;
    newConfig.geometry = MemberBoxGeometry{angle, QRect(x, y, width, height)};
    return newConfig;
}

void ConfigBoxes::loadConfigFromJson(QJsonDocument doc){
    mConfigMap.clear();
    QJsonArray root = doc.array();
    for (int i = 0; i < root.size(); i++) {
        QJsonObject configBox = root.at(i).toObject();
        auto const id = configBox.value("id").toString();
        auto const newConfig = readJsonConfigurations(configBox);
        mConfigMap[id] = newConfig;
    }
}

void ConfigBoxes::saveConfig(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw ConfigError{QObject::tr("Cannot open file %1").arg(filename), filename};
        return;
    }
    QJsonArray array;
    for(auto it = mConfigMap.begin(); it != mConfigMap.end(); it++) {
        QJsonObject item;
        item["id"] = it->first;
        saveJsonConfigurations(item, it->second);
        array.append(item);
    }
    auto doc = QJsonDocument(array);
    file.write(doc.toJson());
}

void ConfigBoxes::addRect(MemberBoxGeometry const& rect, const QString &id) {
    JsonConfig newConfig {rect};
    mConfigMap[id] = newConfig;
}

void ConfigBoxes::deleteRect(QString id) {
    if (auto it = mConfigMap.find(id); it != mConfigMap.end()) {
        mConfigMap.erase(it);
    }
}

MemberBoxGeometry ConfigBoxes::getRect(QString id) const{
    if(auto it = mConfigMap.find(id); it != mConfigMap.end()) {
        return it->second.geometry;
    }
    return {};
}
