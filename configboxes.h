#ifndef CONFIGBOXES_H
#define CONFIGBOXES_H

#include <map>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "boxgeometry.h"

struct JsonConfig{
    BoxGeometry geometry;
};

struct ConfigError{
    QString errorMessage;
    QString filename;
};


class ConfigBoxes : public QObject
{
    Q_OBJECT
public:
    ConfigBoxes();
    void loadConfigurationFile(QString filename);
    void loadConfigFromJson(QJsonDocument doc);
    void saveConfig(QString filename);
    JsonConfig readJsonConfigurations(const QJsonObject &json);
    void saveJsonConfigurations(QJsonObject &json, const JsonConfig config);
    void addRect(BoxGeometry rect, QString id);
    BoxGeometry getRect(QString id);
private:
    std::map<QString, JsonConfig> mConfigMap;
};

#endif // CONFIGBOXES_H
