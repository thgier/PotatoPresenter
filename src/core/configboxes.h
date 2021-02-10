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
    void saveConfig(QString filename);
    void addRect(BoxGeometry rect, QString id);
    BoxGeometry getRect(QString id);
    QString getBasePath() const;
private:
    void saveJsonConfigurations(QJsonObject &json, const JsonConfig config);
    JsonConfig readJsonConfigurations(const QJsonObject &json);
    void loadConfigFromJson(QJsonDocument doc);
    std::map<QString, JsonConfig> mConfigMap;
    QString mPath;
};

#endif // CONFIGBOXES_H
