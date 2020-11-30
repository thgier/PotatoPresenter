#ifndef EQUATIONCACHEMANAGER_H
#define EQUATIONCACHEMANAGER_H
#include <QSvgRenderer>
#include <QProcess>
#include <QDebug>
#include <QFile>

enum SvgStatus{
    success,
    error,
    pending,
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
    std::shared_ptr<QSvgRenderer> getCachedImage(QByteArray hash) const;
    void startSvgGeneration(QByteArray hash, QProcess* latex);
    void writeSvgToMap(QByteArray hash);
    void errorOccured(QByteArray hash, QProcess::ProcessError error);
signals:
    void conversionFinished();
    void errorWhileLatexConversion(QString error);
private:
    std::map<QByteArray, SvgEntry> mCachedImages;
    QString mFolder;
    QStringList mRemoveFiles;
    void removeFiles(QByteArray hash);
};

EquationCacheManager& cacheManager();

#endif
