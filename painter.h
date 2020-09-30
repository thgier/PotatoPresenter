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
    QPainter& getPainter();
private:
    QPainter& mPainter;
};

#endif // PAINTER_H
