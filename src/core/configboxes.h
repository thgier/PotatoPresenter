/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef CONFIGBOXES_H
#define CONFIGBOXES_H

#include <map>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "boxgeometry.h"

struct JsonConfig{
    MemberBoxGeometry geometry;
};

struct ConfigError{
    QString errorMessage;
    QString filename;
};

class ConfigBoxes
{
public:
    ConfigBoxes() = default;
    ConfigBoxes(QString filename);

    void saveConfig(QString filename) const;

    void addRect(const MemberBoxGeometry &rect, QString const& id);
    void deleteRect(QString id);
    void deleteAngle(QString id);

    void deleteAllRectsExcept(std::vector<QString> const& boxIds);

    MemberBoxGeometry getRect(QString id) const;

private:
    void saveJsonConfigurations(QJsonObject &json, const JsonConfig config) const;
    JsonConfig readJsonConfigurations(const QJsonObject &json);
    void loadConfigFromJson(QJsonDocument doc);

private:
    std::map<QString, JsonConfig> mConfigMap;
};

#endif // CONFIGBOXES_H
