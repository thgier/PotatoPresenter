#include "boxgeometry.h"
#include <math.h>
#include <QTransform>
#include <numbers>
#include<QDebug>

BoxGeometry::BoxGeometry()
{}

BoxGeometry::BoxGeometry(int x, int y, int width, int height, double angle)
    : mLeft(x)
    , mTop(y)
    , mWidth(width)
    , mHeight(height)
    , mAngle(angle)
{}

QRect BoxGeometry::rect() const {
    return QRect(mLeft.value_or(0), mTop.value_or(0), mWidth.value_or(0), mHeight.value_or(0));
}

std::optional<double> BoxGeometry::angle() const {
    return mAngle;
}

void BoxGeometry::setAngle(double angle) {
    mAngle = angle;
    if(mAngle < 0){
        mAngle = mAngle.value() + 360;
    }
}

void BoxGeometry::addAngle(qreal dAngle) {
    mAngle = mAngle.value() +  dAngle;
    mAngle = int(mAngle.value()) % 360;
}

pointPosition BoxGeometry::classifyPoint(QPoint point, int margin) const {
    point = transform().inverted().map(point);
    auto const positionRect = rect();
    if((positionRect.topLeft() - point).manhattanLength() < margin) {
        return pointPosition::topLeftCorner;
    }
    else if((positionRect.bottomLeft() - point).manhattanLength() < margin) {
        return pointPosition::bottomLeftCorner;
    }
    else if((positionRect.bottomRight() - point).manhattanLength() < margin) {
        return pointPosition::bottomRightCorner;
    }
    else if((positionRect.topRight() - point).manhattanLength() < margin) {
        return pointPosition::topRightCorner;
    }
    else if(abs(positionRect.top() - point.y()) < margin) {
        return pointPosition::topBorder;
    }
    else if(abs(positionRect.bottom() - point.y()) < margin) {
        return pointPosition::bottomBorder;
    }
    else if(abs(positionRect.left() - point.x()) < margin) {
        return pointPosition::leftBorder;
    }
    else if(abs(positionRect.right() - point.x()) < margin) {
        return pointPosition::rightBorder;
    }
    else if(positionRect.contains(point)) {
        return pointPosition::inBox;
    }
    else {
        return pointPosition::notInBox;
    }
}

bool BoxGeometry::contains(QPoint point, int margin) const {
    point = transform().inverted().map(point);
    auto const rectMargin = rect().marginsAdded(QMargins(margin, margin, margin, margin));
    return rectMargin.contains(point);
}

bool BoxGeometry::contains(QPoint point) const {
    point = transform().inverted().map(point);
    return rect().contains(point);
}

QTransform BoxGeometry::transform() const {
    return transform(rect().center());
}

QTransform BoxGeometry::transform(QPoint rotatingPoint) const {
    QTransform transform;
    transform.translate(rotatingPoint.x(), rotatingPoint.y());
    transform.rotate(mAngle.value());
    transform.translate(-rotatingPoint.x(), -rotatingPoint.y());
    return transform;

}

QTransform BoxGeometry::rotateTransform() const {
    QTransform transform;
    transform.rotate(mAngle.value());
    return transform;
}

qreal BoxGeometry::lengthDiagonal() {
    return std::sqrt(mWidth.value() * mWidth.value() + mHeight.value() * mHeight.value());
}
