/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "template.h"
#include "utils.h"
#include <QFile>
#include <algorithm>

namespace  {
void addVariableIfNotExist(Variables & variables, Variables const& addedVariables) {
    for(auto const& addedVariable: addedVariables) {
        if(variables.find(addedVariable.first) == variables.end()) {
            variables[addedVariable.first] = addedVariable.second;
        }
    }
}
}

Template::Template()
{

}

Template::Template(SlideList slides)
{
    setSlides(slides);
}

void Template::setConfig(ConfigBoxes config) {
    mPresentation.setConfig(config);
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


void Template::setSlides(SlideList slides) {
    mPresentation.setData({slides, nullptr});
    mVariables = slides.lastSlide()->variables();
}

void Template::applyTemplate(SlideList& slideList) {
    mPresentation.applyDefinedClass(slideList);
    for(auto const& slide: slideList.vector) {
        auto const slideclass = slide->slideClass();
        auto const boxlist = getTemplateSlide(slideclass);
        slide->setTemplateBoxes(copy(boxlist));
        addVariableIfNotExist(slide->variables(), mVariables);
    }
}


Variables const& Template::variables() {
    return mVariables;
}
