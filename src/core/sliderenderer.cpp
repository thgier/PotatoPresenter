/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "sliderenderer.h"

namespace {

bool boxGetPainted(Pause boxPause, int currentPauseCounter) {
    switch(boxPause.mDisplayMode) {
        case PauseDisplayMode::fromPauseOn:
            if(boxPause.mCount <= currentPauseCounter) {
                return true;
            }
            break;
        case PauseDisplayMode::onlyInPause:
            if(boxPause.mCount == currentPauseCounter) {
                return true;
            }
            break;
    }
    return false;
};

};

SlideRenderer::SlideRenderer(QPainter& painter)
    : mPainter(painter)
{
}

void SlideRenderer::paintSlide(Slide::Ptr slide) const {
    paintSlide(slide, slide->numberPauses());
}

void SlideRenderer::paintSlide(Slide::Ptr slide, int pauseCount) const {
    if(slide->empty()) {
        return;
    }
    auto const templateBoxes = slide->templateBoxes();
    auto const variables = slide->variables();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter, variables, mRenderHints);
    }
    auto const& boxes = slide->boxes();
    for(auto const& box: boxes){
        // boxes get only painted when pause counter conform
        auto const pause = box->pauseCounter();

        if(boxGetPainted(pause, pauseCount)) {
            box->drawContent(mPainter, variables, mRenderHints);
        }
    }
}

QPainter& SlideRenderer::painter() const {
    return mPainter;
}

void SlideRenderer::setRenderHints(PresentationRenderHints hints) {
    mRenderHints = hints;
}
