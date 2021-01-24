#include "arrowbox.h"
#include <QPainterPath>

ArrowBox::ArrowBox(BoxGeometry rect, QString id)
    : Box(rect, id)
{
}

void ArrowBox::drawContent(QPainter& painter){
    startDraw(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto const rect = geometry().rect();
    QPainterPath path;
    int const w = double(rect.height()) / 3;
    int const arrowW = 150;
    path.addRect(rect.left(), rect.center().y() - w/2, rect.width() - arrowW, w);
    path.moveTo(rect.right(), rect.center().y());
    path.lineTo(rect.right() - arrowW, rect.top());
    path.lineTo(rect.right() - arrowW, rect.bottom());
    path.moveTo(rect.right(), rect.center().y());

    painter.setBrush(mStyle.mColor);
    painter.drawPath(path);
    endDraw(painter);
}
