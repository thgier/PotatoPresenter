#include "presentation.h"
#include <QFileInfo>
#include <QDir>
#include <QBuffer>

Presentation::Presentation() : QObject()
{
}

void Presentation::loadInput(QString configFilename) {
    mConfig.loadConfigurationFile(configFilename);
}

FrameList Presentation::frameList() const {
    return mFrames;
}

void Presentation::setFrames(const FrameList &frames) {
    mFrames = frames;
    applyConfiguration();
    Q_EMIT presentationChanged();
}

void Presentation::setBoxGeometry(const QString &boxId, const BoxGeometry &rect, int pageNumber) {
    auto const& box = mFrames.findBox(boxId);
    if(!box) {
        return;
    }
    box->setGeometry(rect);
    mConfig.addRect(rect, boxId);
    Q_EMIT frameChanged(pageNumber);
}

void Presentation::deleteBoxGeometry(const QString &boxId, int pageNumber) {
    mConfig.deleteRect(boxId);
    Q_EMIT frameChanged(pageNumber);
}

void Presentation::saveConfig(QString const& file) {
    mConfig.saveConfig(file);
}

ConfigBoxes& Presentation::configuration() {
    return mConfig;
}

void Presentation::applyConfiguration() {
    for(auto const& frame: mFrames.vector) {
        for(auto const& box: frame->boxes()) {
            auto const config = mConfig.getRect(box->id());
            if(!config.isEmpty()) {
                box->setGeometry(mConfig.getRect(box->id()));
            }
        }
    }
}

QSize Presentation::dimensions() const {
    return mDimensions;
}
