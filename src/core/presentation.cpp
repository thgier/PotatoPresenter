/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "presentation.h"
#include "template.h"
#include <QFileInfo>
#include <QDir>
#include <QBuffer>
#include <QDebug> 

Presentation::Presentation() : QObject()
{
}

void Presentation::loadInput(QString configFilename) {
    mConfig.loadConfigurationFile(configFilename);
}

SlideList Presentation::slideList() const {
    return mSlides;
}

void Presentation::setTemplate(Template::Ptr templateObject) {
    mTemplate = templateObject;
}

void Presentation::setSlides(const SlideList &slides) {
    mSlides = slides;
    applyConfiguration();
    if(mTemplate) {
        mTemplate->applyTemplate(mSlides);
    }
    else {
        mSlides = applyStandardTemplate(slides);
    }
    Q_EMIT presentationChanged();
}

void Presentation::setBoxGeometry(const QString &boxId, BoxGeometry const& rect, int pageNumber) {
    auto const& box = mSlides.findBox(boxId);
    if(!box) {
        return;
    }
    box->setGeometry(rect);
    mConfig.addRect(rect.toValue(), boxId);
    Q_EMIT slideChanged(pageNumber);
}

void Presentation::deleteBoxGeometry(const QString &boxId, int pageNumber) {
    mConfig.deleteRect(boxId);
    Q_EMIT slideChanged(pageNumber);
}

void Presentation::saveConfig(QString const& file) {
    mConfig.saveConfig(file);
}

ConfigBoxes& Presentation::configuration() {
    return mConfig;
}

void Presentation::setConfig(ConfigBoxes config) {
    mConfig = config;
    Q_EMIT rebuildNeeded();
}

void Presentation::applyConfiguration() {
    for(auto const& slide: mSlides.vector) {
        for(auto const& box: slide->boxes()) {
            auto const config = mConfig.getRect(box->configId());
            if(config.empty()) {
                continue;
            }
            box->geometry().setLeftIfNotSet(config.rect.left());
            box->geometry().setTopIfNotSet(config.rect.top());
            box->geometry().setWidthIfNotSet(config.rect.width());
            box->geometry().setHeightIfNotSet(config.rect.height());
            box->geometry().setAngleIfNotSet(config.angle);
        }
    }
}

const SlideList &Presentation::applyStandardTemplate(const SlideList &slides) const {
    //TODO: Standard Template that makes sense
    for(auto const& slide: slides.vector) {
        for(auto const& box: slide->boxes()) {
            applyStandardTemplateToBox(box);
        }
    }
    return slides;
}

QSize Presentation::dimensions() const {
    return mDimensions;
}

int Presentation::numberOfSlides() const {
    return mSlides.numberSlides();
}

Box::Ptr Presentation::findBox(const QString &id) const {
    if(id.startsWith("intern")) {
        for(auto const& slide: mSlides.vector) {
            if(id.contains(slide->id())) {
                for(auto const& box: slide->boxes()) {
                    if(box->id() == id) {
                        return box;
                    }
                }
            }
        }
    }
    else{
        for(auto const& slide: mSlides.vector) {
            for(auto const& box: slide->boxes()) {
                if(box->id() == id) {
                    return box;
                }
            }
        }
    }
    return {};
}

std::pair<Slide::Ptr, Box::Ptr> Presentation::findBoxForLine(int line) const {
    if(mSlides.empty()) {
        return {};
    }
    qInfo() << "lines;";
    for(auto const& slide: mSlides.vector) {
        qInfo() << slide->line();
    }
    qInfo() << "line" << line;
    auto slide = std::lower_bound(mSlides.vector.begin(), mSlides.vector.end(), line,
                     [](auto const& a, auto b){return a->line() <= b;});
    if(slide == mSlides.vector.begin()) {
        return {};
    }
    slide--;
    auto box = std::lower_bound(slide->get()->boxes().begin(), slide->get()->boxes().end(), line,
                               [](auto const& a, auto b){return a->line() <= b;});
    if(box == slide->get()->boxes().begin()) {
        return {*slide, nullptr};
    }
    box--;
    return std::pair(*slide, *box);
}

void Presentation::applyStandardTemplateToBox(Box::Ptr box) const {
    QRect rect;
    auto style = box->style();
    if(style.getClass() == "title") {
        rect = QRect(50, 40, 1500, 100);
        if(!style.mFontWeight.has_value()) {
            style.mFontWeight = FontWeight::bold;
        }
        if(!style.mFontSize.has_value()) {
            style.mFontSize = 80;
        }
    }
    else if(style.getClass() == "body") {
        rect = QRect(50, 150, 1500, 650);
    }
    else if(style.getClass() == "right_column") {
        rect = QRect(830, 150, 720, 650);
    }
    else if(style.getClass() == "left_column") {
        rect = QRect(50, 150, 720, 650);
    }
    else if(style.getClass() == "fullscreen") {
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
    for(auto const& slide: mSlides.vector) {
        for(auto const& box: slide->boxes()) {
            ids.push_back(box->id());
        }
    }
    mConfig.deleteAllRectsExcept(ids);
}
