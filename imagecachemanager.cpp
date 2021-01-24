#include "imagecachemanager.h"
#include <filesystem>
#include <QDir>
#include <QDebug>

ImageCacheManager::ImageCacheManager()
{
    mWatcher = new QFileSystemWatcher(this);
    QTimer *fileTimer = new QTimer(this);
    fileTimer->setSingleShot(true);
    connect(mWatcher, &QFileSystemWatcher::fileChanged,
            this, [this, fileTimer](QString path){fileTimer->start(200);
                                       mLastPath = path;});
    connect(fileTimer, &QTimer::timeout,
            this, [this](){reloadImage(mLastPath);});

    QTimer *dirTimer = new QTimer(this);
    dirTimer->setSingleShot(true);
    connect(mWatcher, &QFileSystemWatcher::directoryChanged,
            this, [this, dirTimer](QString path){dirTimer->start(200);
                                       mLastPathDir = path;});
    connect(dirTimer, &QTimer::timeout,
            this, [this](){removeFailed(mLastPathDir);});

}

ImageCacheManager& cacheManagerImages()
{
    static ImageCacheManager instance;
    return instance;
}

std::shared_ptr<QImage> ImageCacheManager::getImage(QString path) {
    if(mCachedImages.find(path) != mCachedImages.end()) {
        return mCachedImages[path].image;
    }
    auto image = std::make_shared<QImage>(path);
    auto dir = QFileInfo(path);
    ImageEntry imageEntry;
    if(dir.exists()){
        mWatcher->addPath(path);
        imageEntry = ImageEntry{image, imageStatus::ok};
    }
    else{
        addFailedToWatcher(dir);
        imageEntry = ImageEntry{image, imageStatus::failed};
    }
    mCachedImages[path] = imageEntry;
    return image;
}

void ImageCacheManager::reloadImage(QString const &path){    
    auto const image = std::make_shared<QImage>(path);
    auto dir = QFileInfo(path);
    ImageEntry imageEntry;
    if(dir.exists()){
        imageEntry = ImageEntry{image, imageStatus::ok};
    }
    else{
        addFailedToWatcher(dir);
        imageEntry = ImageEntry{image, imageStatus::failed};
    }
    mCachedImages[path] = imageEntry;
    emit imageChanged();
}

void ImageCacheManager::removeFailed(QString path){
    for(auto const& entry: mCachedImages){
        if(entry.second.status == imageStatus::failed && entry.first.contains(path)){
            mCachedImages.erase(entry.first);
        }
    }
    mWatcher->removePath(path);
    emit imageChanged();
}

void ImageCacheManager::addFailedToWatcher(QFileInfo file){
    auto pathRecursive = file.absoluteDir();
    while(!pathRecursive.exists() && !pathRecursive.isEmpty()){
        pathRecursive.cdUp();
    }
    QString name = pathRecursive.canonicalPath();
    mWatcher->addPath(name);
    auto list = mWatcher->directories();
    auto listfiles = mWatcher->files();
}

void ImageCacheManager::deleteAllResources(){
    mCachedImages.clear();
    mWatcher = new QFileSystemWatcher(this);
    emit imageChanged();
}
