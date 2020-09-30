#ifndef BOX_H
#define BOX_H

#include <QRect>
#include <QPainter>

class Box
{
public:
    Box();
    Box(QRect rect);
    QRect Rect();
    virtual void drawContent(QPainter& painter);
protected:
    void setRect(QRect rect);
private:
    QRect mRect;
};

#endif // BOX_H
