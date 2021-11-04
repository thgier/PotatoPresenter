#include "templatecache.h"


TemplateCache::TemplateCache()
{
    mWatcher = new QFileSystemWatcher(this);
    connect(mWatcher, &QFileSystemWatcher::fileChanged,
            [this](QString){mTemplate = nullptr;
            Q_EMIT templateChanged();});
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
