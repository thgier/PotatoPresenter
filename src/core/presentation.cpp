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

namespace {
void forEachBox(auto const& slides, auto func) {
    for (auto const& slide: slides.vector)
        for (auto const& box: slide->boxes())
            func(slide, box);
}

BoxStyle& setStyleIfNotSet(BoxStyle & appliedStyle, BoxStyle const& modelStyle) {
    auto const assignIfUnset = [](auto& value, auto const& standard) {
        if(!value) {
            value = standard;
        }
    };

    // set style to standartstyle if not set by property
    assignIfUnset(appliedStyle.mFont, modelStyle.font());
    assignIfUnset(appliedStyle.mFontSize, modelStyle.fontSize());
    assignIfUnset(appliedStyle.mFontWeight, modelStyle.fontWeight());
    assignIfUnset(appliedStyle.mColor, modelStyle.color());
    assignIfUnset(appliedStyle.mBackgroundColor, modelStyle.mBackgroundColor);
    assignIfUnset(appliedStyle.mAlignment, modelStyle.alignment());
    assignIfUnset(appliedStyle.mLineSpacing, modelStyle.linespacing());
    assignIfUnset(appliedStyle.mOpacity, modelStyle.opacity());
    assignIfUnset(appliedStyle.mText, modelStyle.text());

    return appliedStyle;
}

void applyGeometryIfNotSet(BoxStyle &appliedStyle, const BoxGeometry &rect) {
    appliedStyle.mGeometry.setLeftIfNotSet(rect.left());
    appliedStyle.mGeometry.setTopIfNotSet(rect.top());
    appliedStyle.mGeometry.setWidthIfNotSet(rect.width());
    appliedStyle.mGeometry.setHeightIfNotSet(rect.height());
    appliedStyle.mGeometry.setAngleIfNotSet(rect.angle());
}

void applyStandardTemplateToBox(Box::Ptr box) {
    QRect rect;
    auto style = box->style();

    // set standart geometry
    if(style.getClass() == "title") {
        rect = QRect(50, 40, 1500, 100);
    }
    else if(style.getClass() == "body") {
        rect = QRect(50, 150, 1500, 650);
    }
    else if(style.getClass() == "image") {
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

    applyGeometryIfNotSet(style, BoxGeometry(rect, 0));
    box->setBoxStyle(style);
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
    mSlides = data.mSlideList;
    mTemplate = data.mTemplate;
    applyConfigurationTemplate();
    Q_EMIT slideChanged(0, mSlides.numberSlides());
}

void Presentation::applyConfigurationTemplate() {
    applyConfiguration();
    createMapDefinesClass();
    applyDefinedClass(mSlides);
    if(mTemplate) {
        mTemplate->applyTemplate(mSlides);
    }
    else {
        applyStandardTemplate(mSlides);
    }
    setTitleIfTextUnset(mSlides);
}

const SlideList &Presentation::slideList() const {
    return mSlides;
}

void Presentation::setBoxGeometry(const QString &boxId, BoxGeometry const& rect, int pageNumber) {
    auto const& box = mSlides.findBox(boxId);
    if(!box) {
        return;
    }
    box->setGeometry(rect);
    mConfig.addRect(rect.toValue(), boxId);
    Q_EMIT slideChanged(pageNumber, pageNumber);
}

void Presentation::deleteBoxGeometry(const QString &boxId, int pageNumber) {
    mConfig.deleteRect(boxId);
    findBox(boxId)->setGeometry(BoxGeometry());
    applyConfigurationTemplate();
    Q_EMIT slideChanged(pageNumber, pageNumber);
}

void Presentation::deleteBoxAngle(const QString &boxId, int pageNumber) {
    mConfig.deleteAngle(boxId);
    auto const box = findBox(boxId);
    auto const rect = box->geometry().rect();
    findBox(boxId)->setGeometry(BoxGeometry(rect, 0));
    applyConfigurationTemplate();
    Q_EMIT slideChanged(pageNumber, pageNumber);
}

const ConfigBoxes &Presentation::configuration() const {
    return mConfig;
}

void Presentation::setConfig(ConfigBoxes config) {
    mConfig = config;
    Q_EMIT rebuildNeeded();
}

void Presentation::applyConfiguration() {
    forEachBox(mSlides, [this](Slide::Ptr slide, Box::Ptr box){
        auto const config = mConfig.getRect(box->configId());
        if(config.empty()) {
            return;
        }
        box->geometry().setLeftIfNotSet(config.rect.left());
        box->geometry().setTopIfNotSet(config.rect.top());
        box->geometry().setWidthIfNotSet(config.rect.width());
        box->geometry().setHeightIfNotSet(config.rect.height());
        box->geometry().setAngleIfNotSet(config.angle);
    });
}

void Presentation::applyDefinedClass(const SlideList &slides) {
    auto const definedClasses = createMapDefinesClass();
    forEachBox(slides, [&definedClasses](Slide::Ptr slide, Box::Ptr box){
        auto const slideKey = slide->slideClass();
        if(!box->style().mClass){
            return;
        }
        BoxStyle definedClassStyle;
        auto const boxKey = "-" + box->style().mClass.value();
        if(definedClasses.find(boxKey) != definedClasses.end()) {
            definedClassStyle = definedClasses.find(boxKey)->second;
        }
        else if(definedClasses.find(slideKey + boxKey) != definedClasses.end()) {
            definedClassStyle = definedClasses.find(slideKey + boxKey)->second;
        }
        else {
            return;
        }
        auto style = box->style();
        applyGeometryIfNotSet(style, definedClassStyle.mGeometry);
        style = setStyleIfNotSet(style, definedClassStyle);
        box->setBoxStyle(style);
    });
}

void Presentation::setTitleIfTextUnset(const SlideList &slides) {
    forEachBox(slides, [](Slide::Ptr slide, Box::Ptr box){
        if(box->style().mClass == "title" && box->style().text().isEmpty()) {
            auto style = box->style();
            style.mText = slide->id();
            box->setBoxStyle(style);
        }
    });
}


void Presentation::applyStandardTemplate(SlideList &slides) const {
    forEachBox(slides, [](Slide::Ptr slide, Box::Ptr box){
        applyStandardTemplateToBox(box);
    });
}

QSize Presentation::dimensions() const {
    return mDimensions;
}

int Presentation::numberOfSlides() const {
    return mSlides.numberSlides();
}

namespace  {

}

Box::Ptr Presentation::findBox(const QString &id) const {
    if(id.startsWith("intern")) {
        auto const box = findBoxCondition(mSlides.vector, [id](auto const& slide, auto const& box) {
            return id.contains(slide->id()) && box->id() == id;
        });
        if (box)
            return box;
    }

    else{
        auto const box = findBoxCondition(mSlides.vector, [id](auto const& slide, auto const& box) {
            return box->id() == id;
        });
        if (box)
            return box;
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



void Presentation::deleteNotNeededConfigurations() {
    std::vector<QString> ids;
    forEachBox(mSlides, [&ids](Slide::Ptr slide, Box::Ptr box){
        ids.push_back(box->id());
    });
    mConfig.deleteAllRectsExcept(ids);
}


std::map<QString, BoxStyle> const Presentation::createMapDefinesClass() const {
    std::map<QString, BoxStyle> definitionClass;
    forEachBox(mSlides, [&definitionClass](Slide::Ptr slide, Box::Ptr box){
        if(box->style().mDefineclass) {
            auto const key = slide->definesClass() + "-" + box->style().mDefineclass.value();
            definitionClass[key] = box->style();
        }
    });
    return definitionClass;
}

QString Presentation::title() const {
    if(mSlides.empty()) {
        return "presentation";
    }
    auto const& variables = mSlides.lastSlide()->variables();
    auto const& title = variables.find("%{title}");
    if(title == variables.end()) {
        return "presentation";
    }
    return title->second;
}
