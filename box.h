#ifndef BOX_H
#define BOX_H

#include <QRect>
#include <QPainter>
#include "boxgeometry.h"

struct BoxStyle{
    int mFontSize = 50;
    QColor mColor{Qt::black};
    QString mFont = "sans-serif";
    qreal mOpacity = 1;
};

class Box : public QObject
{
    Q_OBJECT
public:
    Box();
    Box(BoxGeometry rect, QString id);
    BoxGeometry geometry();
    virtual void drawContent(QPainter& painter);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setRect(BoxGeometry rect);
    void startDraw(QPainter& painter);
    void endDraw(QPainter& painter);
    void drawBoundingBox(QPainter& painter);
    void drawScaleMarker(QPainter& painter, int size);
    QString id();
    void setBoxStyle(BoxStyle style);
protected:
    BoxStyle mStyle;
private:
    BoxGeometry mRect;
    QString mId = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
