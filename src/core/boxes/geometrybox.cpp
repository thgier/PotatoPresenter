/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "geometrybox.h"

namespace {

QRect squaredBoundingRect(QRect const & rect) {
    QRect boundingRect;
    if (rect.width() > rect.height()) {
        auto const left = rect.left() + (rect.width() - rect.height()) / 2;
        boundingRect = QRect(left, rect.top(), rect.height(), rect.height());
    }
    else {
        auto const top = rect.top() + (rect.height() - rect.width()) / 2;
        boundingRect = QRect(rect.left(), top, rect.width(), rect.width());
    }
    return boundingRect;
}

QPainterPath pathOfArrow(QRect const& rect) {
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
    return path;
}

QPainterPath pathOfCircle(QRect const& rect) {
    QPainterPath myPath;
    myPath.addEllipse(squaredBoundingRect(rect));
    return myPath;
}

QPainterPath pathOfEllipse(QRect const& rect) {
    QPainterPath path;
    path.addEllipse(rect);
    return path;
}

QPainterPath pathOfRect(QRect const& rect) {
    QPainterPath path;
    path.addRect(rect);
    return path;
}

QPainterPath pathOfSquare(QRect const& rect) {
    QPainterPath path;
    path.addRect(squaredBoundingRect(rect));
    return path;
}

QPainterPath painterPath(QString shape, QRect rect) {
    if(shape == "arrow") {
        return pathOfArrow(rect);
    }
    if(shape == "circle") {
        return pathOfCircle(rect);
    }
    if(shape == "ellipse") {
        return pathOfEllipse(rect);
    }
    if(shape == "square") {
        return pathOfSquare(rect);
    }
    return pathOfRect(rect);
}
}

void GeometryBox::drawContent(QPainter& painter, std::map<QString, QString> const&, PresentationRenderHints hints){
    auto const rect = style().paintableRect();
    mPainterPath = painterPath(style().text(), rect);
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(mStyle.color());
    painter.drawPath(mPainterPath);
}

bool GeometryBox::containsPoint(QPoint point, int) const {
    return mPainterPath.contains(geometry().transform().inverted().map(point));
}

