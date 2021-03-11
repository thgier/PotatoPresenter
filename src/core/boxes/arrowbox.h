#ifndef ARROWBOX_H
#define ARROWBOX_H

#include "box.h"
#include <QPainterPath>

class ArrowBox : public Box
{
public:
    ArrowBox(BoxStyle style, QString id, int line);

    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
    bool containsPoint(QPoint point, int) const override;

private:
    QPainterPath mPainterPath;
};

#endif // ARROWBOX_H
