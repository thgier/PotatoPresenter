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

struct PixMapElement {
    std::shared_ptr<QPixmap> mPixmap;
    QRect mBoundingBox;
};

struct PixMapVector {
    std::vector<PixMapElement> mPixmaps;

    void insertPixmap(PixMapElement pixmap) {
        mPixmaps.insert(mPixmaps.begin(), pixmap);
        if(mPixmaps.size() > 2) {
            mPixmaps.pop_back();
        }
    };

    PixMapElement findPixMap(QSize size) {
        for (auto const& pixmapElement : mPixmaps) {
            if(pixmapElement.mPixmap->size() == size) {
                return pixmapElement;
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

