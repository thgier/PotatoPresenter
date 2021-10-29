#ifndef LATEXBOX_H
#define LATEXBOX_H

#include "box.h"

class LaTeXBox : public Box
{
public:
    LaTeXBox(QString text);

    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;

private:
    QString mText;
};

#endif // LATEXBOX_H
