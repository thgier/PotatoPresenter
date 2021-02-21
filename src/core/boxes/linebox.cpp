#include "linebox.h"

#include <QPainterPath>

LineBox::LineBox(BoxGeometry rect, QString id)
    : Box(rect, id)
{
}

void LineBox::drawContent(QPainter& painter, std::map<QString, QString>){
    PainterTransformScope scope(this, painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto const left = QPoint(geometry().rect().left(), geometry().rect().center().y());
    auto const right = QPoint(geometry().rect().right(), geometry().rect().center().y());
    painter.drawLine(left, right);
}
