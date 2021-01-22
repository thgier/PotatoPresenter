#include "imagecachemanager.h"
#include <filesystem>
#include <QDir>
#include <QDebug>

ImageCacheManager::ImageCacheManager()
{
    mTimer->setSingleShot(true);
    connect(&mWatcher, &QFileSystemWatcher::fileChanged,
            this, [this](QString path){mTimer->start(200);
                                       mLastPath = path;});
    connect(mTimer, &QTimer::timeout,
            this, [this](){reloadImage(mLastPath);});

    QTimer *dirTimer = new QTimer(this);
    dirTimer->setSingleShot(true);
    connect(&mWatcher, &QFileSystemWatcher::directoryChanged,
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
    qInfo() << "watched Directories: " << mWatcher.directories();
    qInfo() << "watched Files: " << mWatcher.files();
    if(mCachedImages.find(path) != mCachedImages.end()) {
        return mCachedImages[path].image;
    }
    auto dir = QFileInfo(path);
    Image imageEntry;
    auto image = std::make_shared<QImage>(path);
    if(dir.exists()){
        mWatcher.addPath(path);
        imageEntry = Image{image, imageStatus::ok};
    }
    else{
        addFailureToWatcher(dir);
        imageEntry = Image{image, imageStatus::failed};
    }
    mCachedImages[path] = imageEntry;
    return image;
}

void ImageCacheManager::updateImage(const QString &path){
    if(mCachedImages.find(path) != mCachedImages.end()) {
//        existing image was loaded sucessfull before
        reloadImage(path);
    }
    else{
//        path is no file but a directory, that is watched due to a failed loading of a image
//        remove all images with failed status from cache which contains path
        removeFailed(path);
    }
}

void ImageCacheManager::reloadImage(QString const &path){    
    auto const image = std::make_shared<QImage>(path);
    auto dir = QFileInfo(path);
    Image imageEntry;
    if(dir.exists()){
        imageEntry = Image{image, imageStatus::ok};
    }
    else{
        addFailureToWatcher(dir);
        imageEntry = Image{image, imageStatus::failed};
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
    mWatcher.removePath(path);
    emit imageChanged();
}

void ImageCacheManager::addFailureToWatcher(QFileInfo file){
    auto pathRecursive = file.absoluteDir();
    while(!pathRecursive.exists() && !pathRecursive.isEmpty()){
        pathRecursive.cdUp();
    }
    QString name = pathRecursive.canonicalPath();
    mWatcher.addPath(name);
    auto list = mWatcher.directories();
    auto listfiles = mWatcher.files();
}
