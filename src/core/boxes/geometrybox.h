#ifndef GEOMETRYBOX_H
#define GEOMETRYBOX_H


#include "box.h"
#include <QPainterPath>

class GeometryBox : public Box
{
public:
    GeometryBox(QString shape);

    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
    bool containsPoint(QPoint point, int) const override;

private:
    // ths shape is set when constructed,
    // the path changes by every redraw and is saved for the function containsPoint
    QString mShape;
    QPainterPath mPainterPath;
};
#endif // GEOMETRYBOX_H
