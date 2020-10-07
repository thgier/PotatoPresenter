#ifndef BOX_H
#define BOX_H

#include <QRect>
#include <QPainter>

class Box
{
public:
    Box();
    Box(QRect rect, int idNumber);
    QRect Rect();
    virtual void drawContent(QPainter& painter);
    void drawBoundingBox(QPainter& painter);
    void translateBox(QPoint translation);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setBoundingBox(bool box);
    void setRect(QRect rect);
    int id();
protected:
    bool mBoundingBox = false;
private:
    QRect mRect;
    int mIDNumber = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
