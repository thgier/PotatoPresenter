#ifndef ARROWBOX_H
#define ARROWBOX_H

#include "box.h"

class ArrowBox : public Box
{
public:
    ArrowBox(BoxGeometry rect, QString id);
    void drawContent(QPainter& painter) override;
};

#endif // ARROWBOX_H
