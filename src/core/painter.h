#ifndef PAINTER_H
#define PAINTER_H
#include "frame.h"
#include "box.h"

#include<QPainter>

class Painter
{
public:
    Painter();
    Painter(QPainter& painter);

//    Painting Frame, if paintFrame(Frame::Ptr frame) is used every Box is painted
    void paintFrame(Frame::Ptr frame) const;
    void paintFrame(Frame::Ptr frame, int pauseCount) const;

    QPainter& painter() const;

private:
    QPainter& mPainter;
};

#endif // PAINTER_H
