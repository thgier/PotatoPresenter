#ifndef IMAGECACHEMANAGER_H
#define IMAGECACHEMANAGER_H
#include <QString>
#include <QImage>
#include <QFileInfo>
#include <map>
#include <memory>
#include <QFileSystemWatcher>
#include <QTimer>
#include <vector>

enum imageStatus{
    ok,
    failed
};

struct Image{
    std::shared_ptr<QImage> image;
    imageStatus status;
};

class ImageCacheManager : public QObject
{
    Q_OBJECT
public:
    ImageCacheManager();
    std::map<QString, Image> mCachedImages;
    std::shared_ptr<QImage> getImage(QString path);
    void updateImage(QString const &path);
    void reloadImage(QString const &path);
    void removeFailed(QString path);
    void addFailureToWatcher(QFileInfo file);
signals:
    void imageChanged();
private:
    QFileSystemWatcher mWatcher;
    QString mLastPath;
    QString mLastPathDir;
    QTimer *mTimer = new QTimer(this);
    std::vector<QString> paths;
};

ImageCacheManager& cacheManagerImages();

#endif // IMAGECACHEMANAGER_H
