#ifndef IMAGECACHEMANAGER_H
#define IMAGECACHEMANAGER_H
#include <QString>
#include <QImage>
#include <map>
#include <memory>
#include <QFileSystemWatcher>


class ImageCacheManager : public QObject
{
    Q_OBJECT
public:
    ImageCacheManager();
    std::map<QString, std::shared_ptr<QImage>> mCachedImages;
    std::shared_ptr<QImage> getImage(QString path);
    void reloadImage(QString const &path);
signals:
    void imageChanged();
private:
    QFileSystemWatcher mWatcher;

};

ImageCacheManager& cacheManagerImages();

#endif // IMAGECACHEMANAGER_H
