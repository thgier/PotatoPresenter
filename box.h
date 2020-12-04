#ifndef BOX_H
#define BOX_H

#include <QRect>
#include <QPainter>

class Box : public QObject
{
    Q_OBJECT
public:
    Box();
    Box(QRect rect, int idNumber);
    QRect Rect();
    virtual void drawContent(QPainter& painter);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setRect(QRect rect);
    int id();
protected:
    int mFontSize = 50;
    QString mFont = "DejaVu Sans";
private:
    QRect mRect;
    int mIDNumber = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
