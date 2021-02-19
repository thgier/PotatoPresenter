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
    void paintFrame(std::shared_ptr<Frame> frame);
    void paintFrame(std::shared_ptr<Frame> frame, int pauseCount);
    QPainter& getPainter();
private:
    QPainter& mPainter;
    int mPageNumber = 0;
};

#endif // PAINTER_H
