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
    drawScaleMarker(painter);
}

void Box::translateBox(QPoint translation) {
    if(mMovable){
        mRect.translate(translation);
        emit rectChanged(Rect(), mIDNumber);
    }
}

void Box::setVisibility(bool vis){
    mVisible = vis;
}

void Box::setMovable(bool move) {
    mMovable = move;
}

void Box::setBoundingBoxVisible(bool box) {
    mBoundingBox = box;
}

int Box::id() {
    return mIDNumber;
}

void Box::drawScaleMarker(QPainter& painter){
    painter.setBrush(Qt::black);
    auto const w = 5;
    painter.drawEllipse(Rect().topLeft(), w, w);
    painter.drawEllipse(Rect().topRight(), w, w);
    painter.drawEllipse(Rect().bottomLeft(), w, w);
    painter.drawEllipse(Rect().bottomRight(), w, w);
    painter.setBrush(Qt::NoBrush);
}

void Box::scaleTopLeft(QPoint scale){
    auto const point = Rect().bottomRight();
    auto const width = Rect().width() - scale.x();
    auto const heigth = Rect().height() - scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveBottomRight(point);
    mRect = Rect().normalized();
}

void Box::scaleTopRight(QPoint scale){
    auto const point = Rect().bottomLeft();
    auto const width = Rect().width() + scale.x();
    auto const heigth = Rect().height() - scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveBottomLeft(point);
    mRect = Rect().normalized();
}

void Box::scaleBottomLeft(QPoint scale){
    auto const point = Rect().topRight();
    auto const width = Rect().width() - scale.x();
    auto const heigth = Rect().height() + scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveTopRight(point);
    mRect = Rect().normalized();
}

void Box::scaleBottomRight(QPoint scale){
    auto const point = Rect().topLeft();
    auto const width = Rect().width() + scale.x();
    auto const heigth = Rect().height() + scale.y();
    mRect.setSize(QSize(width, heigth));
    mRect.moveTopRight(point);
    mRect = Rect().normalized();
}
