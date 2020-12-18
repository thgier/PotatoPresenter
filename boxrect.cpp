#include "boxrect.h"
#include <math.h>
#include <QTransform>
#include <numbers>
#include<QDebug>

BoxRect::BoxRect()
    : mAngle{0}
{}

BoxRect::BoxRect(QRect rect, qreal angle)
    : mRect{rect}, mAngle{angle}
{
}

BoxRect::BoxRect(QRect rect)
    : mRect{rect}
{
}

BoxRect::BoxRect(int x, int y, int width, int height)
    : mRect(QRect(x, y, width, height))
{}

QRect BoxRect::rect() const{
    return mRect;
}

qreal BoxRect::angle() const{
    return mAngle;
}

void BoxRect::setRect(QRect rect){
    mRect = rect;
}

void BoxRect::setAngle(qreal angle){
    mAngle = angle;
}

void BoxRect::addAngle(qreal dAngle){
    mAngle += dAngle;
    while(mAngle > 360){
        mAngle -= 360;
    }
}

pointPosition BoxRect::includePoint(QPoint point, int margin) const{
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

bool BoxRect::contains(QPoint point) const{
    point = transform().inverted().map(point);
    return mRect.contains(point);
}

QTransform BoxRect::transform() const{
    QTransform transform;
    transform.translate(mRect.center().x(), mRect.center().y());
    transform.rotate(mAngle);
    transform.translate(-mRect.center().x(), -mRect.center().y());
    return transform;
}

QTransform BoxRect::rotateTransform() const{
    QTransform transform;
    transform.rotate(mAngle);
    return transform;
}

qreal BoxRect::distanceToAngle(qreal x) const{
    auto const r = std::sqrt((1.0*mRect.width() * mRect.width() + 1.0*mRect.height() * mRect.height())) / 2;
    if(r == 0){
        return 0;
    }
    qWarning() << "angle" << x / r * 180 / std::numbers::pi;
    return x / r * 180.0 / std::numbers::pi;
}

bool BoxRect::isEmpty() const{
    return mRect.isEmpty();
}
