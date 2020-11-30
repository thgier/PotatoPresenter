#ifndef LAYOUT_H
#define LAYOUT_H

#include <QSize>
#include <QRect>
#include "box.h"

enum aspectRatio {
  sixteenToNine,
};

class Layout
{
public:
    Layout(aspectRatio ratio);
    aspectRatio mAspectRatio;
    QSize mSize;
    QRect mTitlePos;
    QRect mBodyPos;
    QRect mFullPos;
    QRect mLeftPos;
    QRect mRightPos;
private:
};

#endif // LAYOUT_H
