/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "templatecache.h"


TemplateCache::TemplateCache()
{
    mWatcher = new QFileSystemWatcher(this);
    connect(mWatcher, &QFileSystemWatcher::fileChanged,
            [this](QString){
            Q_EMIT templateChanged();
        });
}

Template::Ptr TemplateCache::getTemplate(QString path) const {
    if (path == mPath) {
        return mTemplate;
    }
    return {};
}

void TemplateCache::setTemplate(Template::Ptr newTemplate, QString path) {
    mPath = path;
    mTemplate = newTemplate;
    mWatcher->addPath(path + ".txt");
    mWatcher->addPath(path + ".json");
}

void TemplateCache::resetTemplate() {
    if(!mPath.isEmpty()) {
        mWatcher->removePath(mPath);
    }
    mPath = "";
    mTemplate.reset();
}
