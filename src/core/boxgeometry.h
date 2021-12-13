/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef BOXRECT_H
#define BOXRECT_H

#include <optional>
#include <QRect>
#include <QTransform>

struct MemberBoxGeometry {
    double angle = 0;
    QRect rect;

    bool empty() const {
        return rect.isEmpty();
    }
};

enum pointPosition{
    inBox,
    topBorder,
    bottomBorder,
    leftBorder,
    rightBorder,
    topLeftCorner,
    bottomLeftCorner,
    bottomRightCorner,
    topRightCorner,
    notInBox
};

struct BoxGeometry
{
public:
    BoxGeometry();
    BoxGeometry(int x, int y, int width, int height, double angle);
    BoxGeometry(QRect rect, double angle);
    BoxGeometry(MemberBoxGeometry memberboxgeometry);

    // return value when it is set otherwise some standard value
    QRect rect() const;
    QRectF rectF() const;
    QSize size() const;
    QPoint topLeft() const;
    double angleDisplay() const;
    int leftDisplay() const;
    int topDisplay() const;
    int widthDisplay() const;
    int heightDisplay() const;
    std::optional<double> angle() const;
    std::optional<int> left() const;
    std::optional<int> top() const;
    std::optional<int> width() const;
    std::optional<int> height() const;
    MemberBoxGeometry toValue() const;

    // set the value
    void setRect(QRect rect);
    void setRect(QRectF rect);
    void setAngle(double angle);
    void setLeft(int left);
    void setTop(int top);
    void setWidth(int width);
    void setHeight(int height);
    void addAngle(qreal dAngle);

    // classify given point
    pointPosition classifyPoint(QPoint point, int margin) const;
    bool contains(QPoint point, int margin) const;
    bool contains(QPoint point) const;

    // get transformation of box
    QTransform transform() const;
    QTransform transform(QPoint rotatingPoint) const;
    QTransform transform(QPointF rotatingPoint) const;
    QTransform rotateTransform() const;

    qreal lengthDiagonal() const;

    // true if one member has value
    bool empty() const;

private:
    // member get value while the document get translated
    std::optional<int> mLeft;
    std::optional<int> mTop;
    std::optional<int> mWidth;
    std::optional<int> mHeight;
    std::optional<double> mAngle;
};

#endif // BOXRECT_H
