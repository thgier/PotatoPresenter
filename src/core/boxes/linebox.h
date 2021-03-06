#ifndef LINEBOX_H
#define LINEBOX_H

#include "box.h"


class LineBox : public Box
{
public:
    LineBox(BoxStyle style, QString id, int line);
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // LINEBOX_H
