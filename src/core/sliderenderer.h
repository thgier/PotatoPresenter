/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

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

    void setRenderHints(PresentationRenderHints hints);

    QPainter& painter() const;

private:
    QPainter& mPainter;
    PresentationRenderHints mRenderHints = NoRenderHints;
};

#endif // PAINTER_H
