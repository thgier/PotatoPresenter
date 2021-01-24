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

struct ImageEntry{
    std::shared_ptr<QImage> image;
    imageStatus status;
};

class ImageCacheManager : public QObject
{
    Q_OBJECT
public:
    ImageCacheManager();
    std::map<QString, ImageEntry> mCachedImages;
    std::shared_ptr<QImage> getImage(QString path);
    void updateImage(QString const &path);
    void reloadImage(QString const &path);
    void removeFailed(QString path);
    void addFailedToWatcher(QFileInfo file);
    void deleteAllResources();
signals:
    void imageChanged();
private:
    QFileSystemWatcher *mWatcher;
    QString mLastPath;
    QString mLastPathDir;
};

ImageCacheManager& cacheManagerImages();

#endif // IMAGECACHEMANAGER_H
