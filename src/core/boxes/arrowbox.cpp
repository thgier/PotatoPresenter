/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "arrowbox.h"

void ArrowBox::drawContent(QPainter& painter, std::map<QString, QString>){
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto const rect = geometry().rect();
    QPainterPath path;
    int const w = double(rect.height()) / 4;
    int arrowW = 100;
    if(rect.width() < 300){
        arrowW = rect.width() / 3;
    }

    path.moveTo(rect.left(), rect.center().y() - w/2);
    path.lineTo(rect.left(), rect.center().y() + w/2);
    path.lineTo(rect.right() - arrowW, rect.center().y() + w/2);
    path.lineTo(rect.right() - arrowW, rect.bottom());
    path.lineTo(rect.right(), rect.center().y());
    path.lineTo(rect.right() - arrowW, rect.top());
    path.lineTo(rect.right() - arrowW, rect.center().y() - w/2);
    path.lineTo(rect.left(), rect.center().y() - w/2);

    painter.setBrush(mStyle.color());
    painter.drawPath(path);
    mPainterPath = path;
}

bool ArrowBox::containsPoint(QPoint point, int) const {
    return mPainterPath.contains(geometry().transform().inverted().map(point));
}
