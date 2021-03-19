#include "sliderenderer.h"

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
        box->drawContent(mPainter, variables);
    }
    auto const& boxes = slide->boxes();
    for(auto const& box: boxes){
        bool boxGetPainted = false;
        // boxes get only painted when pause counter conform
        auto const [boxPauseCounter, boxPauseMode] = box->pauseCounter();
        switch(boxPauseMode) {
            case PauseDisplayMode::fromPauseOn:
                if(boxPauseCounter <= pauseCount) {
                    boxGetPainted = true;
                }
                break;
            case PauseDisplayMode::onlyInPause:
                if(boxPauseCounter == pauseCount) {
                    boxGetPainted = true;
                }
                break;
        }
        if(boxGetPainted) {
            box->drawContent(mPainter, variables);
        }
    }
}

QPainter& SlideRenderer::painter() const {
    return mPainter;
}
