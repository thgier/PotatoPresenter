#include "linebox.h"

#include <QPainterPath>

LineBox::LineBox(BoxStyle style, QString id, int line)
    : Box(style, id, line)
{
}

void LineBox::drawContent(QPainter& painter, std::map<QString, QString>){
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto const left = QPoint(geometry().left(), geometry().rect().center().y());
    auto const right = QPoint(geometry().rect().right(), geometry().rect().center().y());
    painter.drawLine(left, right);
}
