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
    int left = -1;
    int top = -1;
    int width = -1;
    int height = -1;
    qreal angle = -1;
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
    Box(BoxGeometry geometry, QString id);
    BoxGeometry geometry() const;
    BoxStyle style() const;
    virtual void drawContent(QPainter& painter, std::map<QString, QString> variables);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setGeometry(BoxGeometry geometry);
    void drawBoundingBox(QPainter& painter);
    void drawScaleMarker(QPainter& painter, int size);
    QString id();
    void setBoxStyle(BoxStyle style);
protected:
    QString substituteVariables(QString text, std::map<QString, QString> variables) const;
    void startDraw(QPainter& painter);
    void endDraw(QPainter& painter) const;
    BoxStyle mStyle;
private:
    BoxGeometry mGeometry;
    QString mId = 0;
    bool mVisible = true;
    bool mMovable = true;
};

#endif // BOX_H
