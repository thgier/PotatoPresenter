#include "imagecachemanager.h"
#include <filesystem>
#include <QDebug>

ImageCacheManager::ImageCacheManager()
{
    connect(&mWatcher, &QFileSystemWatcher::fileChanged,
            this,  &ImageCacheManager::reloadImage);
}

ImageCacheManager& cacheManagerImages()
{
    static ImageCacheManager instance;
    return instance;
}

std::shared_ptr<QImage> ImageCacheManager::getImage(QString path) {
    if(mCachedImages.find(path) != mCachedImages.end()) {
        return mCachedImages[path];
    }
    if(std::filesystem::exists(path.toStdString())){
        qWarning() << "add path successed " << mWatcher.addPath(path);
        auto image = std::make_shared<QImage>(path);
        mCachedImages[path] = image;
        return image;
    }
    return nullptr;
}

void ImageCacheManager::reloadImage(QString const &path){
    if(std::filesystem::exists(path.toStdString())){
        auto image = std::make_shared<QImage>(path);
        mCachedImages[path] = image;
    }
    else{
        mCachedImages.erase(path);
    }
    emit imageChanged();
}
