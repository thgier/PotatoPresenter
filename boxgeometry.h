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

struct BoxGeometry
{
public:
    BoxGeometry();
    BoxGeometry(QRect rect, qreal angle);
    BoxGeometry(QRect rect);
    BoxGeometry(int x, int y, int width, int height);
    QRect rect() const;
    qreal angle() const;
    void setRect(QRect rect);
    void setAngle(qreal angle);
    void addAngle(qreal dAngle);
    pointPosition classifyPoint(QPoint point, int margin) const;
    bool contains(QPoint point, int margin) const;
    bool contains(QPoint point) const;
    QTransform transform() const;
    QTransform transform(QPoint rotatingPoint) const;
    QTransform transformCenter() const;
    QTransform rotateTransform() const;
    QTransform tranformLeftBottom() const;
    qreal distanceToAngle(qreal x) const;
    bool isEmpty() const;
    qreal lengthDiagonal();
    void moveBottomLeft(QPoint point);
    void setTopRight(QPoint point);
private:
    QRect mRect;
    qreal mAngle = 0;
};

#endif // BOXRECT_H
