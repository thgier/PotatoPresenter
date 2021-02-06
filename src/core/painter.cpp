#include "painter.h"

Painter::Painter(QPainter& painter)
    : mPainter(painter)
{
}

void Painter::paintFrame(std::shared_ptr<Frame> frame){
    auto templateBoxes = frame->getTemplateBoxes();
    auto const variables = frame->Variables();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter, variables);
    }
    auto boxes = frame->getBoxes();
    for(auto const& box: boxes){
        box->drawContent(mPainter, variables);
    }
}

QPainter& Painter::getPainter(){
    return mPainter;
}
