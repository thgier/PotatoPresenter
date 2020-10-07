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
    mRect = rect;
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

void Box::drawBoundingBox(QPainter& painter) {
    auto pen = painter.pen();
    auto const sizePen = 0.1;
    pen.setWidth(sizePen);
    painter.setPen(pen);
    auto brush = painter.brush();
    brush.setStyle(Qt::NoBrush);
    painter.setBrush(brush);
    painter.translate(QPoint(0, -sizePen));
    painter.drawRect(Rect());
}

void Box::translateBox(QPoint translation) {
    if(mMovable){
        mRect.translate(translation);
    }
}

void Box::setVisibility(bool vis){
    mVisible = vis;
}

void Box::setMovable(bool move) {
    mMovable = move;
}

void Box::setBoundingBox(bool box) {
    mBoundingBox = box;
}

int Box::id() {
    return mIDNumber;
}

