#include "painter.h"

Painter::Painter(QPainter& painter)
    : mPainter(painter)
{
}

void Painter::paintFrame(std::shared_ptr<Frame> frame){
    auto boxes = frame->getBoxes();
    for(auto const& box: boxes){
        box->drawContent(mPainter);
    }
}

QPainter& Painter::getPainter(){
    return mPainter;
}
