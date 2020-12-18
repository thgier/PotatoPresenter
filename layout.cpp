#include "layout.h"

Layout::Layout(aspectRatio ratio)
    : mAspectRatio{ratio}
{
    switch (mAspectRatio) {
        case aspectRatio::sixteenToNine:
            mSize = QSize(1600, 900);
            mTitlePos = BoxRect(50, 50, 1500, 100);
            mBodyPos = BoxRect(50, 200, 1500, 650);
            mFullPos = BoxRect(0, 0, 1600, 900);
            mLeftPos = BoxRect(50, 200, 720, 650);
            mRightPos = BoxRect(830, 200, 720, 650);
            mPresTitlePos = BoxRect(100, 350, 1400, 100);
            mSubtitlePos = BoxRect(100, 500, 1400, 100);
//            mSize = QSize(160, 90);
//            mTitlePos = QRect(5, 5, 150, 10);
//            mBodyPos = QRect(5, 20, 150, 65);
//            mFullPos = QRect(1, 1, 158, 88);
//            mLeftPos = QRect(5, 20, 72, 65);
//            mRightPos = QRect(83, 20, 72, 65);
//            mSize = QSize(2667, 1500);
//            mTitlePos = QRect(83, 83, 2500, 167);
//            mBodyPos = QRect(83, 333, 2500, 1083);
//            mFullPos = QRect(17, 17, 2634, 1467);
//            mLeftPos = QRect(83, 333, 1200, 1083);
//            mRightPos = QRect(1384, 333, 1200, 1083);
            break;
    }

}
