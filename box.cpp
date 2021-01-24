#include "box.h"

Box::Box(BoxGeometry rect, QString id)
    : mRect{rect}
    , mId{id}
{
}

void Box::setRect(BoxGeometry rect){
    if(mMovable){
        mRect = rect;
    }
}

BoxGeometry Box::geometry(){
    return mRect;
}

void Box::drawContent(QPainter& painter) {
    startDraw(painter);
    auto pen = painter.pen();
    auto const sizeBrush = 0.1;
    pen.setWidth(sizeBrush);
    painter.setPen(pen);
    painter.translate(QPoint(0, -sizeBrush));
    painter.drawRect(mRect.rect());
    painter.rotate(-mRect.angle());
    endDraw(painter);
}


void Box::setVisibility(bool vis){
    mVisible = vis;
}

void Box::setMovable(bool move) {
    mMovable = move;
}

QString Box::id() {
    return mId;
}

void Box::startDraw(QPainter &painter){
    painter.save();
    painter.setTransform(mRect.transform());
    painter.setOpacity(mStyle.mOpacity);
}

void Box::endDraw(QPainter &painter){
    painter.restore();
}

void Box::drawBoundingBox(QPainter &painter){
    startDraw(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto pen = painter.pen();
    auto const sizePen = 0.1;
    pen.setWidth(sizePen);
    painter.setPen(pen);
    painter.translate(QPoint(0, -sizePen));
    painter.drawRect(mRect.rect());
    endDraw(painter);
}

void Box::drawScaleMarker(QPainter &painter, int size){
    size /= 2;
    startDraw(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    QPoint(size/2, size/2);
    painter.fillRect(QRect(mRect.rect().topLeft() + QPoint(-size/2, -size/2), QSize(size, size)), Qt::black);
    painter.fillRect(QRect(mRect.rect().topRight() + QPoint(size/2, -size/2), QSize(-size, size)), Qt::black);
    painter.fillRect(QRect(mRect.rect().bottomLeft() + QPoint(-size/2, size/2), QSize(size, -size)), Qt::black);
    painter.fillRect(QRect(mRect.rect().bottomRight() + QPoint(size/2, size/2), QSize(-size, -size)), Qt::black);

    endDraw(painter);
}

void Box::setBoxStyle(BoxStyle style){
    mStyle = style;
}
