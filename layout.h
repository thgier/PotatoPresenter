#ifndef LAYOUT_H
#define LAYOUT_H

#include <QSize>
#include "box.h"
#include "boxrect.h"

enum aspectRatio {
  sixteenToNine,
};

class Layout
{
public:
    Layout(aspectRatio ratio);
    aspectRatio mAspectRatio;
    QSize mSize;
    BoxRect mTitlePos;
    BoxRect mBodyPos;
    BoxRect mFullPos;
    BoxRect mLeftPos;
    BoxRect mRightPos;
    BoxRect mPresTitlePos;
    BoxRect mSubtitlePos;
private:
};

#endif // LAYOUT_H
