#include "boxgeometry.h"
#include <math.h>
#include <QTransform>
#include <numbers>
#include<QDebug>

BoxGeometry::BoxGeometry()
    : mAngle{0}
{}

BoxGeometry::BoxGeometry(QRect rect, qreal angle)
    : mRect{rect}, mAngle{angle}
{
}

BoxGeometry::BoxGeometry(QRect rect)
    : mRect{rect}
{
}

BoxGeometry::BoxGeometry(int x, int y, int width, int height)
    : mRect(QRect(x, y, width, height))
{}

QRect BoxGeometry::rect() const{
    return mRect;
}

qreal BoxGeometry::angle() const{
    return mAngle;
}

void BoxGeometry::setRect(QRect rect){
    mRect = rect;
}

void BoxGeometry::setAngle(qreal angle){
    mAngle = angle;
}

void BoxGeometry::addAngle(qreal dAngle){
    mAngle += dAngle;
    while(mAngle > 360){
        mAngle -= 360;
    }
}

pointPosition BoxGeometry::classifyPoint(QPoint point, int margin) const{
    point = transform().inverted().map(point);
    if((mRect.topLeft() - point).manhattanLength() < margin){
        return pointPosition::topLeftCorner;
    }
    else if((mRect.bottomLeft() - point).manhattanLength() < margin){
        return pointPosition::bottomLeftCorner;
    }
    else if((mRect.bottomRight() - point).manhattanLength() < margin){
        return pointPosition::bottomRightCorner;
    }
    else if((mRect.topRight() - point).manhattanLength() < margin){
        return pointPosition::topRightCorner;
    }
    else if(abs(mRect.top() - point.y()) < margin){
        return pointPosition::topBorder;
    }
    else if(abs(mRect.bottom() - point.y()) < margin){
        return pointPosition::bottomBorder;
    }
    else if(abs(mRect.left() - point.x()) < margin){
        return pointPosition::leftBorder;
    }
    else if(abs(mRect.right() - point.x()) < margin){
        return pointPosition::rightBorder;
    }
    else if(mRect.contains(point)){
        return pointPosition::inBox;
    }
    else {
        return pointPosition::notInBox;
    }
}

bool BoxGeometry::contains(QPoint point, int margin) const{
    point = transform().inverted().map(point);
    auto const rectMargin = mRect.marginsAdded(QMargins(margin, margin, margin, margin));
    return rectMargin.contains(point);
}

bool BoxGeometry::contains(QPoint point) const{
    point = transform().inverted().map(point);
    return mRect.contains(point);
}

QTransform BoxGeometry::transform() const{
    QTransform transform;
    transform.translate(mRect.center().x(), mRect.center().y());
    transform.rotate(mAngle);
    transform.translate(-mRect.center().x(), -mRect.center().y());
    return transform;
}

QTransform BoxGeometry::transformCenter() const{
    QTransform transform;
    transform.translate(-mRect.center().x(), -mRect.center().y());
    transform.rotate(mAngle);
    return transform;
}

QTransform BoxGeometry::tranformLeftBottom() const{
    QTransform transform;
    transform.translate(-mRect.bottomLeft().x(), -mRect.bottomLeft().y());
    transform.rotate(mAngle);
    return transform;
}

QTransform BoxGeometry::rotateTransform() const{
    QTransform transform;
    transform.rotate(mAngle);
    return transform;
}

qreal BoxGeometry::distanceToAngle(qreal x) const{
    auto const r = std::sqrt((1.0*mRect.width() * mRect.width() + 1.0*mRect.height() * mRect.height())) / 2;
    if(r == 0){
        return 0;
    }
    qWarning() << "angle" << x / r * 180 / std::numbers::pi;
    return x / r * 180.0 / std::numbers::pi;
}

bool BoxGeometry::isEmpty() const{
    return mRect.isEmpty();
}

qreal BoxGeometry::lengthDiagonal(){
    return std::sqrt(mRect.width() * mRect.width() + mRect.height() * mRect.height());
}

BoxGeometry BoxGeometry::toBottomLeft(){
    auto transformation = transform();
    transformation.translate(mRect.bottomLeft().x(), mRect.bottomLeft().y());
    transformation.rotate(mAngle);
    transformation.translate(-mRect.bottomLeft().x(), -mRect.bottomLeft().y());

}
