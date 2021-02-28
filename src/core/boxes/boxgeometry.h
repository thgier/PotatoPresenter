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
    BoxGeometry(int x, int y, int width, int height, double angle);
    QRect rect() const;
    std::optional<double> angle() const;
    void setRect(QRect rect);
    void setAngle(double angle);
    void addAngle(qreal dAngle);

    pointPosition classifyPoint(QPoint point, int margin) const;
    bool contains(QPoint point, int margin) const;
    bool contains(QPoint point) const;

    QTransform transform() const;
    QTransform transform(QPoint rotatingPoint) const;
    QTransform rotateTransform() const;

    qreal lengthDiagonal();

private:
    std::optional<int> mLeft;
    std::optional<int> mTop;
    std::optional<int> mWidth;
    std::optional<int> mHeight;
    std::optional<double> mAngle = 0;
};

#endif // BOXRECT_H
