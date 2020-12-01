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
    void translateBox(QPoint translation);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setRect(QRect rect);
    int id();
    void scaleTopLeft(QPoint scale);
    void scaleTopRight(QPoint scale);
    void scaleBottomLeft(QPoint scale);
    void scaleBottomRight(QPoint scale);
    void scaleTop(QPoint scale);
    void scaleBottom(QPoint scale);
    void scaleLeft(QPoint scale);
    void scaleRight(QPoint scale);
signals:
    void rectChanged(QRect newRect, int id);
protected:
    int mFontSize = 50;
    QString mFont = "DejaVu Sans";
private:
    QRect mRect;
    int mIDNumber = 0;
    bool mVisible = true;
    bool mMovable = true;
    void boxChanged();
};

#endif // BOX_H
