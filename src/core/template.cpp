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

Template::Template(const SlideList &slides)
    : mData{slides}
{
}

void Template::setConfig(ConfigBoxes config) {
    mData.applyConfiguration(config);
    mConfig = config;
}

Box::List Template::getTemplateSlide(QString slideId) const {
    auto slide = mData.slides().findDefiningSlide(slideId);
    if(!slide){
        return {};
    }
    auto boxes = slide->boxes();
    auto rm = [slideId](std::shared_ptr<Box> box) {return box->style().mDefineclass;};
    boxes.erase(std::remove_if(boxes.begin(), boxes.end(), rm), boxes.end());
    return boxes;
}

void Template::applyTemplate(SlideList& slideList) {
    mData.applyDefinedClass(slideList, mConfig);
    for(auto const& slide: slideList.vector) {
        auto const slideclass = slide->slideClass();
        auto const boxlist = getTemplateSlide(slideclass);
        slide->setTemplateBoxes(copy(boxlist));
        addVariableIfNotExist(slide->variables(), variables());
    }
}


Variables const& Template::variables() {
    return mData.slides().lastSlide()->variables();
}

void Template::setData(PresentationData data) {
    mData = data;
    mData.applyConfiguration(mConfig);
}
