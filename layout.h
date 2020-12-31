#ifndef LAYOUT_H
#define LAYOUT_H

#include <QSize>
#include "box.h"
#include "boxgeometry.h"

enum aspectRatio {
  sixteenToNine,
};

class Layout
{
public:
    Layout(aspectRatio ratio);
    aspectRatio mAspectRatio;
    QSize mSize;
    BoxGeometry mTitlePos;
    BoxGeometry mBodyPos;
    BoxGeometry mFullPos;
    BoxGeometry mLeftPos;
    BoxGeometry mRightPos;
    BoxGeometry mPresTitlePos;
    BoxGeometry mSubtitlePos;
    BoxGeometry mArrowPos;
private:
};

#endif // LAYOUT_H
