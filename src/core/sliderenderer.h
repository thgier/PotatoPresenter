#ifndef PAINTER_H
#define PAINTER_H
#include "slide.h"
#include "box.h"

#include<QPainter>

class SlideRenderer
{
public:
    SlideRenderer();
    SlideRenderer(QPainter& painter);

//    Painting Slide, if paintSlide(Slide::Ptr slide) is used every Box is painted
    void paintSlide(Slide::Ptr slide) const;
    void paintSlide(Slide::Ptr slide, int pauseCount) const;

    QPainter& painter() const;

private:
    QPainter& mPainter;
};

#endif // PAINTER_H
