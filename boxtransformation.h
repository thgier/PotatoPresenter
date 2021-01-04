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
    BoxTransformation();
    BoxTransformation(std::shared_ptr<Box> box, TransformationType trafo, pointPosition posMouseBox, int pageNumber, QPoint mousePos);
    void doTransformation(QPoint mousePos, std::shared_ptr<Presentation> pres);
    BoxGeometry makeScaleTransformation(QPoint mousePos);
    BoxGeometry makeRotateTransformation(QPoint mousePos);

private:
    QRect scale(QPoint mouse, QPointF v, BoxGeometry* boxrect) const;
//    BoxTransformation &operator = (const BoxTransformation &b) { mTrafo = b.mTrafo; return *this; }
    std::shared_ptr<Box> mBox;
    TransformationType mTrafo;
    pointPosition mPosMouseBox;
    int mPageNumber;
    QPoint mLastMousePosition;

};

#endif // BOXTRANSFORMATION_H
