/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

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

BoxGeometry::BoxGeometry(QRect rect, double angle)
    : mLeft(rect.left())
    , mTop(rect.top())
    , mWidth(rect.width())
    , mHeight(rect.height())
    , mAngle(angle)
{}

BoxGeometry::BoxGeometry(MemberBoxGeometry memberboxgeometry)
    : mLeft(memberboxgeometry.rect.left())
    , mTop(memberboxgeometry.rect.top())
    , mWidth(memberboxgeometry.rect.width())
    , mHeight(memberboxgeometry.rect.height())
    , mAngle(memberboxgeometry.angle)
{}

QRect BoxGeometry::rect() const {
    return QRect(mLeft.value_or(0), mTop.value_or(0), mWidth.value_or(300), mHeight.value_or(100));
}

QRectF BoxGeometry::rectF() const {
    return QRectF(mLeft.value_or(0), mTop.value_or(0), mWidth.value_or(300), mHeight.value_or(100));
}

QSize BoxGeometry::size() const {
    return {width(), height()};
}

QPoint BoxGeometry::topLeft() const {
    return {left(), top()};
}

double BoxGeometry::angle() const {
    return mAngle.value_or(0);
}

int BoxGeometry::left() const {
    return mLeft.value_or(0);
}

int BoxGeometry::top() const {
    return mTop.value_or(0);
}

int BoxGeometry::width() const {
    return mWidth.value_or(300);
}

int BoxGeometry::height() const {
    return mHeight.value_or(100);
}

MemberBoxGeometry BoxGeometry::toValue() const {
    return {angle(), QRect(left(), top(), width(), height())};
}

void BoxGeometry::setLeftIfNotSet(int left) {
    mLeft = mLeft.value_or(left);
}

void BoxGeometry::setTopIfNotSet(int top) {
    mTop = mTop.value_or(top);
}

void BoxGeometry::setWidthIfNotSet(int width) {
    mWidth = mWidth.value_or(width);
}

void BoxGeometry::setHeightIfNotSet(int height) {
    mHeight = mHeight.value_or(height);
}

void BoxGeometry::setAngleIfNotSet(double angle) {
    mAngle = mAngle.value_or(angle);
}

void BoxGeometry::setRect(QRect rect) {
    mLeft = rect.left();
    mTop = rect.top();
    mWidth = rect.width();
    mHeight = rect.height();
}

void BoxGeometry::setRect(QRectF rect) {
    setRect(rect);
}

void BoxGeometry::setAngle(double angle) {
    mAngle = angle;
    if(mAngle < 0){
        mAngle = mAngle.value() + 360;
    }
}

void BoxGeometry::setLeft(int left) {
    mLeft = left;
}

void BoxGeometry::setTop(int top) {
    mTop = top;
}

void BoxGeometry::setWidth(int width) {
    mWidth = width;
}

void BoxGeometry::setHeight(int height) {
    mHeight = height;
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

QTransform BoxGeometry::transform(QPointF rotatingPoint) const {
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

qreal BoxGeometry::lengthDiagonal() const {
    return std::sqrt(mWidth.value() * mWidth.value() + mHeight.value() * mHeight.value());
}

bool BoxGeometry::empty() const {
    return !(mLeft.has_value() || mTop.has_value() || mWidth.has_value() || mHeight.has_value() || mAngle.has_value());
}
