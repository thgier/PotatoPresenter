#ifndef BOXRECT_H
#define BOXRECT_H

#include <QRect>
#include <QTransform>

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

struct BoxRect
{
public:
    BoxRect();
    BoxRect(QRect rect, qreal angle);
    BoxRect(QRect rect);
    BoxRect(int x, int y, int width, int height);
    QRect rect() const;
    qreal angle() const;
    void setRect(QRect rect);
    void setAngle(qreal angle);
    void addAngle(qreal dAngle);
    pointPosition includePoint(QPoint point, int margin) const;
    bool contains(QPoint point) const;
    QTransform transform() const;
    QTransform rotateTransform() const;
    qreal distanceToAngle(qreal x) const;
    bool isEmpty() const;
private:
    QRect mRect;
    qreal mAngle = 0;
};

#endif // BOXRECT_H
