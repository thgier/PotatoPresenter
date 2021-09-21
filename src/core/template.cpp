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
