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
void forEachTemplateBox(auto const& slides, auto func) {
    for (auto const& slide: slides.vector)
        for (auto const& box: slide->templateBoxes())
            func(slide, box);
}

void setStyleToBoxIfSetInModel(Box::Ptr box, BoxStyle const& modelStyle) {
    auto const assignIfSet = [](auto& value, auto const& standard) {
        if(standard) {
            value = standard;
        }
    };

    assignIfSet(box->style().mFont, modelStyle.mFont);
    assignIfSet(box->style().mFontSize, modelStyle.mFontSize);
    assignIfSet(box->style().mFontWeight, modelStyle.mFontWeight);
    assignIfSet(box->style().mColor, modelStyle.mColor);
    assignIfSet(box->style().mBackgroundColor, modelStyle.mBackgroundColor);
    assignIfSet(box->style().mAlignment, modelStyle.mAlignment);
    assignIfSet(box->style().mLanguage, modelStyle.mLanguage);
    assignIfSet(box->style().mLineSpacing, modelStyle.mLineSpacing);
    assignIfSet(box->style().mOpacity, modelStyle.mOpacity);
    assignIfSet(box->style().mPadding, modelStyle.mPadding);
    assignIfSet(box->style().mBorderRadius, modelStyle.mBorderRadius);
    assignIfSet(box->style().mTextMarker.color, modelStyle.mTextMarker.color);
    assignIfSet(box->style().mTextMarker.fontWeight, modelStyle.mTextMarker.fontWeight);
    assignIfSet(box->style().mBorder.width, modelStyle.mBorder.width);
    assignIfSet(box->style().mBorder.style, modelStyle.mBorder.style);
    assignIfSet(box->style().mBorder.color, modelStyle.mBorder.color);
    if(modelStyle.mText && !modelStyle.mText->isEmpty()) {
        box->style().mText = modelStyle.mText;
    }
}

void setStyleToBoxIfNotSettedAndSetInModel(Box::Ptr box, BoxStyle const& modelStyle) {
    auto const assignIfSet = [](auto& value, auto const& standard) {
        if(standard && !value) {
            value = standard;
        }
    };

    assignIfSet(box->style().mFont, modelStyle.mFont);
    assignIfSet(box->style().mFontSize, modelStyle.mFontSize);
    assignIfSet(box->style().mFontWeight, modelStyle.mFontWeight);
    assignIfSet(box->style().mColor, modelStyle.mColor);
    assignIfSet(box->style().mBackgroundColor, modelStyle.mBackgroundColor);
    assignIfSet(box->style().mAlignment, modelStyle.mAlignment);
    assignIfSet(box->style().mLanguage, modelStyle.mLanguage);
    assignIfSet(box->style().mLineSpacing, modelStyle.mLineSpacing);
    assignIfSet(box->style().mOpacity, modelStyle.mOpacity);
    assignIfSet(box->style().mPadding, modelStyle.mPadding);
    assignIfSet(box->style().mBorderRadius, modelStyle.mBorderRadius);
    assignIfSet(box->style().mTextMarker.color, modelStyle.mTextMarker.color);
    assignIfSet(box->style().mTextMarker.fontWeight, modelStyle.mTextMarker.fontWeight);
    assignIfSet(box->style().mBorder.width, modelStyle.mBorder.width);
    assignIfSet(box->style().mBorder.style, modelStyle.mBorder.style);
    assignIfSet(box->style().mBorder.color, modelStyle.mBorder.color);
    if(modelStyle.mText && !modelStyle.mText->isEmpty()) {
        box->style().mText = modelStyle.mText;
    }
}

void applyGeometryToBoxIfSetInModel(Box::Ptr box, const BoxGeometry &modelGeometry) {

    if(modelGeometry.left()) {
        box->geometry().setLeft(modelGeometry.leftDisplay());
    }
    if(modelGeometry.top()) {
        box->geometry().setTop(modelGeometry.topDisplay());
    }
    if(modelGeometry.width()) {
        box->geometry().setWidth(modelGeometry.widthDisplay());
    }
    if(modelGeometry.height()) {
        box->geometry().setHeight(modelGeometry.heightDisplay());
    }
    if(modelGeometry.angle()) {
        box->geometry().setAngle(modelGeometry.angleDisplay());
    }
}

void applyStandardTemplateToBox(Box::Ptr box) {
    QRect rect;
    auto style = box->style();

    // set standard geometry
    if(style.getClass() == "title") {
        rect = QRect(50, 40, 1500, 100);
    }
    else if(style.getClass() == "body") {
        rect = QRect(50, 150, 1500, 650);
    }
    else if(style.getClass() == "code") {
        rect = QRect(50, 150, 1500, 650);
        if(!style.mFont) {
            style.mFont = "DejaVu Sans Mono";
        }
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

    applyGeometryToBoxIfSetInModel(box, BoxGeometry(rect, 0));
}

Box::Ptr findBoxCondition(std::vector<Slide::Ptr> slides, auto func) {
    for (auto const& slide: slides)
        for (auto const& box: slide->boxes())
            if(func(slide, box))
                return box;
    return {};
}

void applyClassIDDefinclass(SlideList & slides) {
    forEachBox(slides, [](Slide::Ptr slide, Box::Ptr box) {
        if(box->properties().find("class") != box->properties().end()) {
            box->style().mClass = box->properties().find("class")->second.mValue;
        }
        if(box->properties().find("id") != box->properties().end()) {
            box->style().mId = box->properties().find("id")->second.mValue;
        }
        if(box->properties().find("defineclass") != box->properties().end()) {
            box->style().mDefineclass = box->properties().find("defineclass")->second.mValue;
        }
    });
}

void applyStandardVariables(SlideList & slides) {
    forEachBox(slides, [](auto const& slide, auto const& box){
        auto const boxStyle = variablesToBoxStyle(slide->variables());
        setStyleToBoxIfNotSettedAndSetInModel(box, boxStyle);
    });

    forEachTemplateBox(slides, [](auto const& slide, auto const& box){
        auto const boxStyle = variablesToBoxStyle(slide->variables());
        setStyleToBoxIfNotSettedAndSetInModel(box, boxStyle);
    });
}

}

Presentation::Presentation() : QObject()
{
}

void Presentation::setData(PresentationData data) {
    mSlides = data.mSlideList;
    mTemplate = data.mTemplate;
    applyConfiguration();
    Q_EMIT slideChanged(0, mSlides.numberSlides());
}

void Presentation::applyConfiguration() {
    applyClassIDDefinclass(mSlides);
    applyStandardTemplate(mSlides);
    if(mTemplate) {
        mTemplate->applyTemplate(mSlides);
    }
    applyDefinedClass(mSlides);

    setTitleIfTextUnset(mSlides);
    applyJSONGeometries();
    applyCSSProperties(mSlides);
}

const SlideList &Presentation::slideList() const {
    return mSlides;
}

const SlideList &Presentation::slideListDefaultApplied() {
    applyStandardVariables(mSlides);
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
    Q_EMIT boxGeometryChanged();
}

void Presentation::deleteBoxGeometry(const QString &boxId, int pageNumber) {
    mConfig.deleteRect(boxId);
    findBox(boxId)->setGeometry(BoxGeometry());
    applyConfiguration();
    Q_EMIT slideChanged(pageNumber, pageNumber);
    Q_EMIT boxGeometryChanged();
}

void Presentation::deleteBoxAngle(const QString &boxId, int pageNumber) {
    mConfig.deleteAngle(boxId);
    auto const box = findBox(boxId);
    auto const rect = box->geometry().rect();
    findBox(boxId)->setGeometry(BoxGeometry(rect, 0));
    applyConfiguration();
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

void Presentation::applyJSONGeometries() {
    forEachBox(mSlides, [this](Slide::Ptr slide, Box::Ptr box){
        applyJSONToBox(slide, box);
    });
}

void Presentation::applyJSONToBox(Slide::Ptr slide, Box::Ptr box) const {
    auto const config = mConfig.getRect(box->configId());
    if(config.empty()) {
        return;
    }
    box->geometry().setLeft(config.rect.left());
    box->geometry().setTop(config.rect.top());
    box->geometry().setWidth(config.rect.width());
    box->geometry().setHeight(config.rect.height());
    box->geometry().setAngle(config.angle);
}

void Presentation::applyDefinedClass(const SlideList &slides) {
    auto const definedClasses = createMapDefinesClass();
    forEachBox(slides, [&definedClasses](Slide::Ptr slide, Box::Ptr box){
        auto const slideKey = slide->slideClass();
        if(!box->style().mClass){
            return;
        }
        auto const boxKey = box->style().mClass.value();
        if(definedClasses.find(boxKey) != definedClasses.end()) {
            auto const definedClassStyle = definedClasses.find(boxKey)->second;
            applyGeometryToBoxIfSetInModel(box, definedClassStyle.mGeometry);
            setStyleToBoxIfSetInModel(box, definedClassStyle);
        }
        if(definedClasses.find(slideKey + "-" + boxKey) != definedClasses.end()) {
            auto const definedClassStyle = definedClasses.find(slideKey + "-" + boxKey)->second;
            applyGeometryToBoxIfSetInModel(box, definedClassStyle.mGeometry);
            setStyleToBoxIfSetInModel(box, definedClassStyle);
        }
        else {
            return;
        }
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


void Presentation::applyStandardTemplate(SlideList &slides) {
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
    Q_EMIT slideChanged(0, mSlides.vector.size());
}


std::map<QString, BoxStyle> Presentation::createMapDefinesClass() const {
    std::map<QString, BoxStyle> definitionClass;
    forEachBox(mSlides, [&definitionClass, this](Slide::Ptr slide, Box::Ptr box){
        if(box->style().mDefineclass) {
            applyJSONToBox(slide, box);
            setStyleToBoxIfSetInModel(box, propertyMapToBoxStyle(box->properties()));
            QString key = "";
            if(!slide->definesClass().isEmpty()) {
                key = slide->definesClass() + "-" ;
            }
            key.append(box->style().mDefineclass.value());
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

void Presentation::applyCSSProperties(const SlideList &slides) {
    auto lambda = [](auto slide, auto box){
        setStyleToBoxIfSetInModel(box, propertyMapToBoxStyle(box->properties()));
    };
    forEachBox(mSlides, lambda);
}

