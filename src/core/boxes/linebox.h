#ifndef LINEBOX_H
#define LINEBOX_H

#include "box.h"


class LineBox : public Box
{
public:
    LineBox(BoxGeometry rect, QString id);
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // LINEBOX_H
