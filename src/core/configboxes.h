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
    ConfigBoxes();

    void loadConfigurationFile(QString filename);
    void saveConfig(QString filename);

    void addRect(const MemberBoxGeometry &rect, QString const& id);
    void deleteRect(QString id);

    void deleteAllRectsExcept(std::vector<QString> const& boxIds);

    MemberBoxGeometry getRect(QString id) const;

private:
    void saveJsonConfigurations(QJsonObject &json, const JsonConfig config);
    JsonConfig readJsonConfigurations(const QJsonObject &json);
    void loadConfigFromJson(QJsonDocument doc);

private:
    std::map<QString, JsonConfig> mConfigMap;
    QString mPath;
};

#endif // CONFIGBOXES_H
