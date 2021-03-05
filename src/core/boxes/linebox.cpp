#include "linebox.h"

#include <QPainterPath>

LineBox::LineBox(BoxStyle style, QString id)
    : Box(style, id)
{
}

void LineBox::drawContent(QPainter& painter, std::map<QString, QString>){
    PainterTransformScope scope(this, painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto const left = QPoint(geometry().left(), geometry().rect().center().y());
    auto const right = QPoint(geometry().rect().right(), geometry().rect().center().y());
    painter.drawLine(left, right);
}
