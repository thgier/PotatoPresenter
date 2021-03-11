#include "framepainter.h"

FramePainter::FramePainter(QPainter& painter)
    : mPainter(painter)
{
}

void FramePainter::paintFrame(Frame::Ptr frame) const {
    paintFrame(frame, frame->numberPauses());
}

void FramePainter::paintFrame(Frame::Ptr frame, int pauseCount) const {
    if(frame->empty()) {
        return;
    }
    auto const templateBoxes = frame->templateBoxes();
    auto const variables = frame->variables();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter, variables);
    }
    auto const& boxes = frame->boxes();
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

QPainter& FramePainter::painter() const {
    return mPainter;
}
