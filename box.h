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

struct VariableSubstitution{
    int begin;
    int end;
    QString word;
};

class Box : public QObject
{
    Q_OBJECT
public:
    using List = std::vector<std::shared_ptr<Box>>;
    Box();
    Box(BoxGeometry rect, QString id);
    BoxGeometry geometry() const;
    BoxStyle style() const;
    virtual void drawContent(QPainter& painter);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setRect(BoxGeometry rect);
    void drawBoundingBox(QPainter& painter);
    void drawScaleMarker(QPainter& painter, int size);
    QString id();
    void setBoxStyle(BoxStyle style);
    QString substituteVariables(QString text, std::map<QString, QString> variables) const;
    void setVariables(std::map<QString, QString> variables);
protected:
    void startDraw(QPainter& painter);
    void endDraw(QPainter& painter);
    BoxStyle mStyle;
    std::map<QString, QString> mVariables;
private:
    BoxGeometry mRect;
    QString mId = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
