/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "configboxes.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <set>

ConfigBoxes::ConfigBoxes(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw ConfigError{"Cannot open file", filename};
        return;
    }
    auto const val = file.readAll();
    auto doc = QJsonDocument::fromJson(val);
    loadConfigFromJson(doc);
    file.close();
}

void ConfigBoxes::saveJsonConfigurations(QJsonObject &json, const JsonConfig config) const {
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

void ConfigBoxes::saveConfig(QString filename) const
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
    file.close();
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

void ConfigBoxes::deleteAngle(QString id) {
    if (auto it = mConfigMap.find(id); it != mConfigMap.end()) {
        auto const rect = it->second.geometry.rect;
        mConfigMap.erase(it);
        mConfigMap[id] = {{0, rect}};
    }
}

void ConfigBoxes::deleteAllRectsExcept(std::vector<QString> const& boxIds) {
    std::set<QString> keepItems;
    std::ranges::copy(boxIds, std::inserter(keepItems, keepItems.begin()));

    auto shouldRemove = [&keepItems](auto const& config) {
        return keepItems.find(config.first) == keepItems.end();
    };
    std::erase_if(mConfigMap, shouldRemove);
}

MemberBoxGeometry ConfigBoxes::getRect(QString id) const{
    if(auto it = mConfigMap.find(id); it != mConfigMap.end()) {
        return it->second.geometry;
    }
    return {};
}
