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
    createMapDefinesClass();
    applyDefinedClass(mSlides);
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

void Presentation::applyDefinedClass(const SlideList &slides) {
    for(auto const& slide: slides.vector) {
        auto const keySlide = slide->slideClass();
        for (auto const& box: slide->boxes()) {
            if(box->style().mClass){
                BoxStyle definedClassStyle;
                if(mDefinedStyles.find("-" + box->style().mClass.value()) != mDefinedStyles.end()) {
                    definedClassStyle = mDefinedStyles.find("-" + box->style().mClass.value())->second;
                }
                else if(mDefinedStyles.find(keySlide + "-" + box->style().mClass.value()) != mDefinedStyles.end()) {
                    definedClassStyle = mDefinedStyles.find(keySlide + "-" + box->style().mClass.value())->second;
                }
                else {
                    continue;
                }
                auto style = box->style();
                applyGeometryIfNotSet(style, definedClassStyle.mGeometry);
                style = setStyleIfNotSet(style, definedClassStyle);
                box->setBoxStyle(style);
            }
        }
    }
}

std::map<QString, BoxStyle> Presentation::definedClasses() const {
    return mDefinedStyles;
}

const SlideList &Presentation::applyStandardTemplate(const SlideList &slides) const {
    for(auto const& slide: slides.vector) {
        auto const standartBoxStyle = slide->standartBoxStyle();
        for(auto const& box: slide->boxes()) {
            applyStandardTemplateToBox(box, standartBoxStyle);
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

void Presentation::applyStandardTemplateToBox(Box::Ptr box, BoxStyle const& standardBoxStyle) const {
    QRect rect;
    auto style = box->style();

    box->setBoxStyle(setStyleIfNotSet(box->style(), standardBoxStyle));

    // set standart geometry
    if(style.getClass() == "title") {
        rect = QRect(50, 40, 1500, 100);
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

    applyGeometryIfNotSet(style, BoxGeometry(rect, 0));
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

BoxStyle Presentation::setStyleIfNotSet(BoxStyle & appliedStyle, BoxStyle const& modelStyle) const {
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

    return appliedStyle;
}

void Presentation::applyGeometryIfNotSet(BoxStyle &appliedStyle, const BoxGeometry &rect) const {
    appliedStyle.mGeometry.setLeftIfNotSet(rect.left());
    appliedStyle.mGeometry.setTopIfNotSet(rect.top());
    appliedStyle.mGeometry.setWidthIfNotSet(rect.width());
    appliedStyle.mGeometry.setHeightIfNotSet(rect.height());
    appliedStyle.mGeometry.setAngleIfNotSet(rect.angle());
}

void Presentation::createMapDefinesClass() {
    for (auto const& slide: mSlides.vector) {
        auto const definitionKeySlide = slide->definesClass();
        for (auto const& box: slide->boxes()) {
            if(box->style().mDefineclass) {
                auto const definitionKey = definitionKeySlide + "-" + box->style().mDefineclass.value();
                mDefinedStyles[definitionKey] = box->style();
            }
        }
    }
}
