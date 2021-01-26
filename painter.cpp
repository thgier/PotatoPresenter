#include "painter.h"

Painter::Painter(QPainter& painter)
    : mPainter(painter)
{
}

void Painter::paintFrame(std::shared_ptr<Frame> frame){
    auto templateBoxes = frame->getTemplateBoxes();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter);
    }
    auto boxes = frame->getBoxes();
    for(auto const& box: boxes){
        box->drawContent(mPainter);
    }
}

QPainter& Painter::getPainter(){
    return mPainter;
}
