#include "painter.h"

Painter::Painter(QPainter& painter)
    : mPainter(painter)
{
}

void Painter::paintFrame(Frame::Ptr frame) const {
    auto const templateBoxes = frame->templateBoxes();
    auto const variables = frame->variables();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter, variables);
    }
    auto const& boxes = frame->boxes();
    for(auto const& box: boxes){
        box->drawContent(mPainter, variables);
    }
}

void Painter::paintFrame(Frame::Ptr frame, int pauseCount) const {
    auto const templateBoxes = frame->templateBoxes();
    auto const variables = frame->variables();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter, variables);
    }
    auto const& boxes = frame->boxes();
    for(auto const& box: boxes){
        if(box->pauseCounterSmaller(pauseCount)) {
            box->drawContent(mPainter, variables);
        }
    }
}

QPainter& Painter::painter() const {
    return mPainter;
}
