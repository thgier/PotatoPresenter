#ifndef LATEXBOX_H
#define LATEXBOX_H

#include "box.h"

class LaTeXBox : public Box
{
public:
    LaTeXBox() = default;

    void drawContent(QPainter& painter, std::map<QString, QString> const& variables, PresentationRenderHints hints = PresentationRenderHints::NoRenderHints) override;
};

#endif // LATEXBOX_H
