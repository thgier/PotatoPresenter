/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef BOXTRANSFORMATION_H
#define BOXTRANSFORMATION_H

#include <math.h>

#include "box.h"
#include "presentation.h"
#include "snapping.h"

enum TransformationType {
    rotate,
    translate
};


struct BoxTransformation
{
public:
    BoxTransformation() = default;
    BoxTransformation(BoxGeometry geometry, TransformationType trafo, pointPosition classifiedMousePosition, QPoint mousePos);
    BoxGeometry doTransformation(QPoint mousePos);
    pointPosition classifiedPoint() const;
    std::optional<int> xGuide() const;
    std::optional<int> yGuide() const;
    bool snapToMiddle() const;
    void setSnapping(Snapping snapping);

private:
    BoxGeometry makeScaleTransformation(QPoint mousePos);
    BoxGeometry makeRotateTransformation(QPoint mousePos);

    QRectF makeSnappingTranslating(QRectF rect);

private:
    BoxGeometry mGeometry;
    TransformationType mTrafo;
    pointPosition mClassifiedMousePosition;
    QPoint mStartMousePosition;
    std::optional<int> mXGuide;
    std::optional<int> mYGuide;
    std::optional<Snapping> mSnapping;
    bool mSnapToMiddle = false;
    int mMargin = 25;
};

#endif // BOXTRANSFORMATION_H
