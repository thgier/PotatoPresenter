/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "template.h"
#include <QFile>
#include <algorithm>

Template::Template()
{

}

Template::Template(SlideList slides)
{
    setSlides(slides);
}

void Template::readTemplateConfig(QString configFile) {
    mPresentation.loadInput(configFile);
}

BoxGeometry Template::getGeometry(QString id) const {
    auto const box = mPresentation.slideList().findBox(id);
    if(box){
        return box->geometry();
    }
    return {};
}

BoxStyle Template::getStyle(QString id, QString slideClass) const {
    auto const slide = mPresentation.slideList().findSlide(slideClass);
    if(!slide) {
        return {};
    }
    auto const box = slide->findDefineBoxClass(id);
    if(box){
        return box->style();
    }
    return {};
}

void Template::declareVariable(QString name, QString value) {
    mVariables[name] = value;
}

void Template::setVariables(std::map<QString, QString> variables) {
    mVariables = variables;
}

Box::List Template::getTemplateSlide(QString slideId) const {
    auto slide = mPresentation.slideList().findDefiningSlide(slideId);
    if(!slide){
        return {};
    }
    auto boxes = slide->boxes();
    auto rm = [slideId](std::shared_ptr<Box> box) {return box->style().mDefineclass;};
    boxes.erase(std::remove_if(boxes.begin(), boxes.end(), rm), boxes.end());
    return boxes;
}

ConfigBoxes& Template::Configuration() {
    return mPresentation.configuration();
}

void Template::setSlides(SlideList slides) {
    mPresentation.setSlides(slides);
}

void Template::applyTemplate(SlideList& slideList) {
    mPresentation.applyDefinedClass(slideList);
    for(auto const& slide: slideList.vector) {
        auto const slideclass = slide->slideClass();
        Box::List boxlist;
        boxlist = getTemplateSlide(slideclass);
        slide->setTemplateBoxes(boxlist);
    }
}

void Template::applyTemplateToBox(Box::Ptr box, QString slideClass) const {
    auto boxStyle = box->style();
    if(!boxStyle.mClass.has_value()) {
        return;
    }
    auto const boxStyleTemplate = getStyle(boxStyle.getClass(), slideClass);
    if(boxStyleTemplate.empty()) {
        mPresentation.applyStandardTemplateToBox(box, boxStyleTemplate);
        return;
    }
    if(!boxStyle.mAlignment) {
        boxStyle.mAlignment = boxStyleTemplate.mAlignment;
    }
    if(!boxStyle.mColor) {
        boxStyle.mColor = boxStyleTemplate.mColor;
    }
    if(!boxStyle.mFont) {
        boxStyle.mFont = boxStyleTemplate.mFont;
    }
    if(!boxStyle.mFontSize) {
        boxStyle.mFontSize = boxStyleTemplate.mFontSize;
    }
    if(!boxStyle.mFontWeight) {
        boxStyle.mFontWeight = boxStyleTemplate.mFontWeight;
    }
    if(!boxStyle.mLineSpacing) {
        boxStyle.mLineSpacing = boxStyleTemplate.mLineSpacing;
    }
    if(!boxStyle.mOpacity) {
        boxStyle.mOpacity = boxStyleTemplate.mOpacity;
    }

    boxStyle.mGeometry.setAngleIfNotSet(boxStyleTemplate.mGeometry.angle());
    boxStyle.mGeometry.setLeftIfNotSet(boxStyleTemplate.mGeometry.left());
    boxStyle.mGeometry.setTopIfNotSet(boxStyleTemplate.mGeometry.top());
    boxStyle.mGeometry.setWidthIfNotSet(boxStyleTemplate.mGeometry.width());
    boxStyle.mGeometry.setHeightIfNotSet(boxStyleTemplate.mGeometry.height());

    box->setBoxStyle(boxStyle);
}

