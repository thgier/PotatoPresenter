/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef IMAGECACHEMANAGER_H
#define IMAGECACHEMANAGER_H

#include <QString>
#include <QImage>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QSvgRenderer>
#include <QPixmap>

#include <map>
#include <memory>
#include <vector>

enum FileLoadStatus{
    ok,
    failed
};

struct PixMapVector {
    std::vector<std::shared_ptr<QPixmap>> mPixmaps;

    void insertPixmap(std::shared_ptr<QPixmap> pixmap) {
        mPixmaps.insert(mPixmaps.begin(), pixmap);
        if(mPixmaps.size() > 2) {
            mPixmaps.pop_back();
        }
    };

    std::shared_ptr<QPixmap> findPixMap(QSize size) {
        for (auto const& pixmap : mPixmaps) {
            if(pixmap->size() == size) {
                return pixmap;
            }
        }
        return {};
    }
};

template <class T>
struct DataEntry{
    std::shared_ptr<T> data;
    FileLoadStatus status;
};

template <class T>
class CacheManager
{
public:    
    DataEntry<T> getData(QString path);
    void setData(QString path, std::shared_ptr<T> data);
    void setCallback(std::function<void(QString)> dataChangedCallback);
    static CacheManager<T>& instance ();
    void deleteFile(QString const &path);
    void deleteAllResources();

private:
    CacheManager();
    CacheManager(CacheManager const&) = delete;
    void updateFile(QString const &path);
    void removeFailed(QString path);
    void addFailedToWatcher(QFileInfo file);

    std::map<QString, DataEntry<T>> mCachedData;
    QFileSystemWatcher *mWatcher;
    QString mLastPath;
    QString mLastPathDir;
    std::function<void(QString)> mDataChangedCallback;
    QTimer mFileTimer;
    QTimer mDirTimer;
};

#endif // IMAGECACHEMANAGER_H

