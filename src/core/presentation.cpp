#include "presentation.h"
#include "template.h"
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

void Presentation::setTemplate(Template *templateObject) {
    mTemplate = templateObject;
}

void Presentation::setFrames(const FrameList &frames) {
    mFrames = frames;
    applyConfiguration();
    if(mTemplate) {
        mTemplate->applyTemplate(mFrames);
    }
    else {
        mFrames = applyStandardTemplate(frames);
    }
    Q_EMIT presentationChanged();
}

void Presentation::setBoxGeometry(const QString &boxId, BoxGeometry &rect, int pageNumber) {
    auto const& box = mFrames.findBox(boxId);
    if(!box) {
        return;
    }
    box->setGeometry(rect);
    mConfig.addRect(rect.toValue(), boxId);
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
            if(!config.empty()) {
                box->setGeometry(config);
            }
        }
    }
}

const FrameList &Presentation::applyStandardTemplate(const FrameList &frames) const {
    //TODO: Standard Template that makes sense
    for(auto const& frame: frames.vector) {
        for(auto const& box: frame->boxes()) {
            applyStandardTemplateToBox(box);
        }
    }
    return frames;
}

QSize Presentation::dimensions() const {
    return mDimensions;
}

void Presentation::applyStandardTemplateToBox(Box::Ptr box) const {
    QRect rect;
    auto style = box->style();
    if(style.boxClass == "title") {
        rect = QRect(50, 40, 1500, 100);
        if(!style.mFontWeight.has_value()) {
            style.mFontWeight = FontWeight::bold;
        }
        if(!style.mFontSize.has_value()) {
            style.mFontSize = 80;
        }
    }
    else if(style.boxClass == "body") {
        rect = QRect(50, 150, 1500, 650);
    }
    else if(style.boxClass == "right_column") {
        rect = QRect(830, 150, 720, 650);
    }
    else if(style.boxClass == "left_column") {
        rect = QRect(50, 150, 720, 650);
    }
    else if(style.boxClass == "fullscreen") {
        rect = QRect(0, 0, 1600, 900);
    }
    else {
        rect = QRect(50, 200, 300, 100);
    }
    style.mGeometry.setLeftIfNotSet(rect.left());
    style.mGeometry.setTopIfNotSet(rect.top());
    style.mGeometry.setWidthIfNotSet(rect.width());
    style.mGeometry.setHeightIfNotSet(rect.height());
    style.mGeometry.setAngleIfNotSet(0);

    box->setBoxStyle(style);
}

void Presentation::deleteNotNeededConfigurations() {
    std::vector<QString> ids;
    for(auto const& frame: mFrames.vector) {
        for(auto const& box: frame->boxes()) {
            ids.push_back(box->id());
        }
    }
    mConfig.deleteAllRectsExcept(ids);
}
