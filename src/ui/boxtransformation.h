#ifndef BOXTRANSFORMATION_H
#define BOXTRANSFORMATION_H

#include <math.h>

#include "box.h"
#include "presentation.h"

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

private:
    BoxGeometry makeScaleTransformation(QPoint mousePos);
    BoxGeometry makeRotateTransformation(QPoint mousePos);

private:
    BoxGeometry mGeometry;
    TransformationType mTrafo;
    pointPosition mClassifiedMousePosition;
    QPoint mStartMousePosition;

};

#endif // BOXTRANSFORMATION_H
