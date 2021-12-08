/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef TEMPLATECACHE_H
#define TEMPLATECACHE_H

#include "template.h"

#include <QFileSystemWatcher>

class TemplateCache : public QObject
{
    Q_OBJECT
public:
    TemplateCache();

    Template::Ptr getTemplate(QString path) const;
    void setTemplate(Template::Ptr newTemplate, QString path);
    void resetTemplate();

Q_SIGNALS:
    void templateChanged();

private:
    Template::Ptr mTemplate;
    QString mPath;
    QFileSystemWatcher *mWatcher;
};

#endif // TEMPLATECACHE_H
