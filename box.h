#ifndef BOX_H
#define BOX_H

#include <QRect>
#include <QPainter>
#include "boxrect.h"

class Box : public QObject
{
    Q_OBJECT
public:
    Box();
    Box(BoxRect rect, QString id);
    BoxRect Rect();
    virtual void drawContent(QPainter& painter);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setRect(BoxRect rect);
    void startDraw(QPainter& painter);
    void endDraw(QPainter& painter);
    void drawBoundingBox(QPainter& painter);
    void drawScaleMarker(QPainter& painter, int size);
    QString id();
protected:
    int mFontSize = 50;
    QString mFont = "DejaVu Sans";
private:
    BoxRect mRect;
    QString mId = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
