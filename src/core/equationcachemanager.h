#ifndef EQUATIONCACHEMANAGER_H
#define EQUATIONCACHEMANAGER_H
#include <QSvgRenderer>
#include <QProcess>
#include <QDebug>
#include <QFile>

enum SvgStatus{
    Success,
    Error,
    Pending,
    NotStarted,
};

struct SvgEntry{
    SvgStatus status;
    std::shared_ptr<QSvgRenderer> svg;
};

class EquationCacheManager : public QObject
{
    Q_OBJECT
public:
    EquationCacheManager();    
    void startConversionProcess(QString mathExpression, QByteArray hash);
    SvgEntry getCachedImage(QByteArray hash) const;
    void startSvgGeneration(QByteArray hash, QProcess* latex);
    void writeSvgToMap(QByteArray hash, QByteArray svg);
    void errorOccured(QByteArray hash, QProcess::ProcessError error);
Q_SIGNALS:
    void conversionFinished();

private:
    QByteArray removeIntegral(QByteArray hash);
    void removeFiles(QByteArray hash);
    QString pathAndFile(QByteArray hash) const;
    QString path(QByteArray hash) const;

private:
    std::map<QByteArray, SvgEntry> mCachedImages;
    QString mFolder;
    QStringList mRemoveFiles;
    int mProcessCounter = 0;
};

EquationCacheManager& cacheManager();

#endif
