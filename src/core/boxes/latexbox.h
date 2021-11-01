#ifndef LATEXBOX_H
#define LATEXBOX_H

#include "box.h"

class LaTeXBox : public Box
{
public:
    LaTeXBox() = default;

    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // LATEXBOX_H
