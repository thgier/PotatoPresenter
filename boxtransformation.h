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
    BoxTransformation(std::shared_ptr<Box> box, TransformationType trafo, pointPosition posMouseBox, int pageNumber);
    void makeTransformation(QPoint mouseMovement, Presentation* pres);
    BoxRect makeScaleTransformation(QPoint mouseMovement);
    BoxRect makeRotateTransformation(QPoint mouseMovement);

private:
    QRect scale(QPoint mouse, QPointF v, BoxRect* boxrect) const;
//    BoxTransformation &operator = (const BoxTransformation &b) { mTrafo = b.mTrafo; return *this; }
    std::shared_ptr<Box> mBox;
    TransformationType mTrafo;
    pointPosition mPosMouseBox;
    int mPageNumber;


};

#endif // BOXTRANSFORMATION_H
