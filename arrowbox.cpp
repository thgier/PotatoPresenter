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

    path.moveTo(rect.left(), rect.center().y() - w/2);
    path.lineTo(rect.left(), rect.center().y() + w/2);
    path.lineTo(rect.right() - arrowW, rect.center().y() + w/2);
    path.lineTo(rect.right() - arrowW, rect.bottom());
    path.lineTo(rect.right(), rect.center().y());
    path.lineTo(rect.right() - arrowW, rect.top());
    path.lineTo(rect.right() - arrowW, rect.center().y() - w/2);
    path.lineTo(rect.left(), rect.center().y() - w/2);

    painter.setBrush(mStyle.mColor);
    painter.drawPath(path);
    endDraw(painter);
}
