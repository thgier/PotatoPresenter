#include "box.h"

Box::Box()
{
    mRect = QRect();
}

Box::Box(QRect rect, int idNumber)
    : mRect{rect}
    , mIDNumber{idNumber}
{
}

void Box::setRect(QRect rect){
    if(mMovable){
        mRect = rect;
    }
}

QRect Box::Rect(){
    return mRect;
}

void Box::drawContent(QPainter& painter) {
    auto pen = painter.pen();
    auto const sizeBrush = 0.1;
    pen.setWidth(sizeBrush);
    painter.setPen(pen);
    painter.translate(QPoint(0, -sizeBrush));
    painter.drawRect(Rect());
}


void Box::setVisibility(bool vis){
    mVisible = vis;
}

void Box::setMovable(bool move) {
    mMovable = move;
}

int Box::id() {
    return mIDNumber;
}

