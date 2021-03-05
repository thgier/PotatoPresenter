#ifndef BOXRECT_H
#define BOXRECT_H

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
    BoxGeometry(MemberBoxGeometry memberboxgeometry);

    // return value when it is set otherwise some standard value
    QRect rect() const;
    QSize size() const;
    QPoint topLeft() const;
    double angle() const;
    int left() const;
    int top() const;
    int width() const;
    int height() const;
    MemberBoxGeometry toValue() const;

    // set only value if std::optional has no value
    void setAngleIfNotSet(double angle);
    void setLeftIfNotSet(int left);
    void setTopIfNotSet(int top);
    void setWidthIfNotSet(int width);
    void setHeightIfNotSet(int height);

    // set the value
    void setRect(QRect rect);
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
