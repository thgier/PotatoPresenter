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

Frame::List Presentation::frames() const {
    return mFrames;
}

void Presentation::setFrames(Frame::List const& frames) {
    mFrames = frames;
    Q_EMIT presentationChanged();
}

bool Presentation::empty() const {
    return mFrames.empty();
}

int Presentation::numberFrames() const {
    return int(mFrames.size());
}

Frame::Ptr Presentation::frameAt(int pageNumber) const {
    return mFrames[pageNumber];
}

void Presentation::setBoxGeometry(const QString &boxId, const BoxGeometry &rect, int pageNumber) {
    auto const& box = findBox(boxId);
    if(!box) {
        return;
    }
    box->setGeometry(rect);
    mConfig.addRect(rect, boxId);
    Q_EMIT frameChanged(pageNumber);
}

Box::Ptr Presentation::findBox(QString const& id) const {
    for(auto const& frame: frames()) {
        if(frame->findBox(id)) {
            return frame->findBox(id);
        }
    }
    return {};
}

Frame::Ptr Presentation::findFrame(const QString &id) const {
    for(auto const &frame: frames()) {
        if(id == frame->id()) {
            return frame;
        }
    }
    return {};
}

void Presentation::saveConfig(QString const& file) {
    mConfig.saveConfig(file);
}

ConfigBoxes& Presentation::configuration() {
    return mConfig;
}

void Presentation::setLayout(Layout layout) {
    mLayout = layout;
}

Layout Presentation::layout() const {
    return mLayout;
}
