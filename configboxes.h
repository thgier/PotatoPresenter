#ifndef CONFIGBOXES_H
#define CONFIGBOXES_H

#include <QRect>
#include <map>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

struct configurations{
    QRect rect;
};


class ConfigBoxes : public QObject
{
    Q_OBJECT
public:
    ConfigBoxes();
    void loadConfigurationFile(QString filename);
    void loadConfigFromJson(QJsonDocument doc);
    void saveConfig();
    configurations readJsonConfigurations(const QJsonObject &json);
    void saveJsonConfigurations(QJsonObject &json, const configurations config);
    void addRect(QRect rect, QString id);
    QRect getRect(QString id);
private:
    std::map<QString, configurations> mConfigMap;
    QString mFilename;
};

#endif // CONFIGBOXES_H
