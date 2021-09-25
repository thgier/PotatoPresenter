/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "cachemanager.h"
#include <filesystem>
#include <QDir>
#include <QDebug>

template <class T>
CacheManager<T>::CacheManager()
{
    mWatcher = new QFileSystemWatcher();
    mFileTimer.setSingleShot(true);
    QObject::connect(mWatcher, &QFileSystemWatcher::fileChanged,
            [this](QString path){mFileTimer.start(200);
                                       mLastPath = path;});
    QObject::connect(&mFileTimer, &QTimer::timeout,
            [this](){deleteFile(mLastPath);});

    mDirTimer.setSingleShot(true);
    QObject::connect(mWatcher, &QFileSystemWatcher::directoryChanged,
            [this](QString path){mDirTimer.start(200);
                                mLastPathDir = path;});
    QObject::connect(&mDirTimer, &QTimer::timeout,
            [this](){removeFailed(mLastPathDir);});

}

template<class T>
CacheManager<T>& CacheManager<T>::instance() {
    static CacheManager<T> cacheManager;
    return cacheManager;
}

template <class T>
void CacheManager<T>::setCallback(std::function<void(QString)> dataChangedCallback){
    mDataChangedCallback = dataChangedCallback;
}

template <class T>
DataEntry<T> CacheManager<T>::getData(QString path) {
    if(mCachedData.find(path) != mCachedData.end()) {
        return mCachedData[path];
    }
    return {};
}

template <class T>
void CacheManager<T>::setData(QString path, std::shared_ptr<T> data){
    if(path.isEmpty()){
        return;
    }
    auto dir = QFileInfo(path);
    DataEntry<T> dataEntry;
    if(!dir.exists() || !data){
        addFailedToWatcher(dir);
        dataEntry = DataEntry<T>{data, FileLoadStatus::failed};
    }
    else{
        mWatcher->addPath(path);
        dataEntry = DataEntry<T>{data, FileLoadStatus::ok};
    }
    mCachedData[path] = dataEntry;
}

template <class T>
void CacheManager<T>::deleteFile(QString const &path){
    mCachedData.erase(path);
    if(mDataChangedCallback){
        mDataChangedCallback(path);
    }
}

template <class T>
void CacheManager<T>::removeFailed(QString path){
    for(auto const& entry: mCachedData){
        if(entry.second.status == FileLoadStatus::failed && entry.first.contains(path)){
            mCachedData.erase(entry.first);
        }
    }
    mWatcher->removePath(path);
    if(mDataChangedCallback){
        mDataChangedCallback(path);
    }
}

template <class T>
void CacheManager<T>::addFailedToWatcher(QFileInfo file){
    auto pathRecursive = file.absoluteDir();
    while(!pathRecursive.exists() && !pathRecursive.isEmpty()){
        pathRecursive.cdUp();
    }
    QString name = pathRecursive.canonicalPath();
    mWatcher->addPath(name);
    auto list = mWatcher->directories();
    auto listfiles = mWatcher->files();
}

template <class T>
void CacheManager<T>::deleteAllResources(){
    mCachedData.clear();
    mWatcher = new QFileSystemWatcher();
    if(mDataChangedCallback){
        mDataChangedCallback(QString());
    }
}

template class CacheManager<QImage>;
template class CacheManager<QSvgRenderer>;
template class CacheManager<PixMapVector>;
