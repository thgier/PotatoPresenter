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

void Box::boxChanged() {
    emit rectChanged(Rect(), mIDNumber);
}

void Box::setRect(QRect rect){
    mRect = rect;
    boxChanged();
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



void Box::translateBox(QPoint translation) {
    if(mMovable){
        mRect.translate(translation);
        boxChanged();
    }
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

void Box::scaleTopLeft(QPoint scale){
    auto const point = Rect().bottomRight();
    auto const width = Rect().width() - scale.x();
    auto const heigth = Rect().height() - scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveBottomRight(point);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleTopRight(QPoint scale){
    auto const point = Rect().bottomLeft();
    auto const width = Rect().width() + scale.x();
    auto const heigth = Rect().height() - scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveBottomLeft(point);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleBottomLeft(QPoint scale){
    auto const point = Rect().topRight();
    auto const width = Rect().width() - scale.x();
    auto const heigth = Rect().height() + scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveTopRight(point);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleBottomRight(QPoint scale){
    auto const point = Rect().topLeft();
    auto const width = Rect().width() + scale.x();
    auto const heigth = Rect().height() + scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveTopLeft(point);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleTop(QPoint scale){
    auto const point = Rect().bottomLeft();
    auto const heigth = Rect().height() - scale.y();
    mRect.setHeight(heigth);
    mRect.moveBottomLeft(point);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleBottom(QPoint scale){
    auto const heigth = Rect().height() + scale.y();
    mRect.setHeight(heigth);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleLeft(QPoint scale){
    auto const point = Rect().topRight();
    auto const width = Rect().width() - scale.x();
    mRect.setWidth(width);
    mRect.moveTopRight(point);
    mRect = Rect().normalized();
    boxChanged();
}

void Box::scaleRight(QPoint scale){
    auto const width = Rect().width() + scale.x();
    mRect.setWidth(width);
    mRect = Rect().normalized();
    boxChanged();
}
