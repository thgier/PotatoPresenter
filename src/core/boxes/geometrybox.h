/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef GEOMETRYBOX_H
#define GEOMETRYBOX_H


#include "box.h"
#include <QPainterPath>

class GeometryBox : public Box
{
public:
    GeometryBox() = default;

    void drawContent(QPainter& painter, std::map<QString, QString> const& variables, PresentationRenderHints hints = PresentationRenderHints::NoRenderHints) override;
    bool containsPoint(QPoint point, int) const override;

    std::shared_ptr<Box> clone() override;

private:
    // ths shape is set when constructed,
    // the path changes by every redraw and is saved for the function containsPoint
    QPainterPath mPainterPath;
};
#endif // GEOMETRYBOX_H
