/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "presentation.h"
#include "template.h"
#include "src/core/utils.h"

#include <QFileInfo>
#include <QDir>
#include <QBuffer>
#include <QDebug> 

namespace {

void forEachBox(auto const& slides, auto func) {
    for (auto const& slide: slides.vector)
        for (auto const& box: slide->boxes())
            func(slide, box);
}

Box::Ptr findBoxCondition(std::vector<Slide::Ptr> slides, auto func) {
    for (auto const& slide: slides)
        for (auto const& box: slide->boxes())
            if(func(slide, box))
                return box;
    return {};
}

}

Presentation::Presentation() : QObject()
{
}

void Presentation::setData(PresentationData data) {
    mData = data;
    mData.applyConfiguration(mConfig);
}

const SlideList &Presentation::slideList() const {
    return mData.slides();
}

void Presentation::setBoxGeometry(const QString &boxId, BoxGeometry const& rect, int pageNumber) {
    auto const& box = mData.slides().findBox(boxId);
    if(!box) {
        return;
    }
    box->setGeometry(rect);
    mConfig.addRect(rect.toValue(), boxId);
    Q_EMIT slideChanged(pageNumber, pageNumber);
    Q_EMIT boxGeometryChanged();
}

void Presentation::deleteBoxGeometry(const QString &boxId, int pageNumber) {
    mConfig.deleteRect(boxId);
    findBox(boxId)->setGeometry(BoxGeometry());
    mData.applyConfiguration(mConfig);
    Q_EMIT slideChanged(pageNumber, pageNumber);
    Q_EMIT boxGeometryChanged();
}

void Presentation::deleteBoxAngle(const QString &boxId, int pageNumber) {
    mConfig.deleteAngle(boxId);
    auto const box = findBox(boxId);
    auto const rect = box->geometry().rect();
    findBox(boxId)->setGeometry(BoxGeometry(rect, 0));
    mData.applyConfiguration(mConfig);
    Q_EMIT slideChanged(pageNumber, pageNumber);
    Q_EMIT boxGeometryChanged();
}

const ConfigBoxes &Presentation::configuration() const {
    return mConfig;
}

void Presentation::setConfig(ConfigBoxes config) {
    mConfig = config;
    Q_EMIT rebuildNeeded();
}




QSize Presentation::dimensions() const {
    return mDimensions;
}

int Presentation::numberOfSlides() const {
    return mData.slides().numberSlides();
}

Box::Ptr Presentation::findBox(const QString &id) const {
    if(id.startsWith("intern")) {
        auto const box = findBoxCondition(mData.slides().vector, [id](auto const& slide, auto const& box) {
            return id.contains(slide->id()) && box->id() == id;
        });
        if (box)
            return box;
    }

    else{
        auto const box = findBoxCondition(mData.slides().vector, [id](auto const& slide, auto const& box) {
            return box->id() == id;
        });
        if (box)
            return box;
    }

    return {};
}

std::pair<Slide::Ptr, Box::Ptr> Presentation::findBoxForLine(int line) const {
    if(mData.slides().empty()) {
        return {};
    }
    qInfo() << "lines;";
    for(auto const& slide: mData.slides().vector) {
        qInfo() << slide->line();
    }
    qInfo() << "line" << line;
    auto slide = std::lower_bound(mData.slides().vector.begin(), mData.slides().vector.end(), line,
                     [](auto const& a, auto b){return a->line() <= b;});
    if(slide == mData.slides().vector.begin()) {
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



void Presentation::deleteNotNeededConfigurations() {
    std::vector<QString> ids;
    forEachBox(mData.slides(), [&ids](Slide::Ptr slide, Box::Ptr box){
        ids.push_back(box->id());
    });
    mConfig.deleteAllRectsExcept(ids);
    Q_EMIT slideChanged(0, mData.slides().numberSlides());
}


QString Presentation::title() const {
    if(mData.slides().empty()) {
        return "presentation";
    }
    auto const& variables = mData.slides().lastSlide()->variables();
    auto const& title = variables.find("%{title}");
    if(title == variables.end()) {
        return "presentation";
    }
    return title->second;
}

PresentationData &Presentation::data() {
    return mData;
}

PresentationData const& Presentation::data() const {
    return mData;
}

