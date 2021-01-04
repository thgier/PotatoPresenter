#ifndef CONFIGBOXES_H
#define CONFIGBOXES_H

#include <map>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "boxgeometry.h"

struct configurations{
    BoxGeometry rect;
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
    configurations readJsonConfigurations(const QJsonObject &json);
    void saveJsonConfigurations(QJsonObject &json, const configurations config);
    void addRect(BoxGeometry rect, QString id);
    BoxGeometry getRect(QString id);
private:
    std::map<QString, configurations> mConfigMap;
    QString mFilename;
};

#endif // CONFIGBOXES_H
