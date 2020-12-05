#ifndef BOX_H
#define BOX_H

#include <QRect>
#include <QPainter>

class Box : public QObject
{
    Q_OBJECT
public:
    Box();
    Box(QRect rect, QString id);
    QRect Rect();
    virtual void drawContent(QPainter& painter);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setRect(QRect rect);
    QString id();
protected:
    int mFontSize = 50;
    QString mFont = "DejaVu Sans";
private:
    QRect mRect;
    QString mId = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
