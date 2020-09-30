#include "box.h"

Box::Box()
{
    mRect = QRect();
}

Box::Box(QRect rect)
    : mRect{rect}
{
}


void Box::setRect(QRect rect){
    mRect = rect;
}

QRect Box::Rect(){
    return mRect;
}

void Box::drawContent(QPainter& painter) {
    painter.drawRect(mRect);
}
