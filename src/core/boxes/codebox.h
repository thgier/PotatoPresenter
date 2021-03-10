#ifndef CODEBOX_H
#define CODEBOX_H

#include "textbox.h"

class CodeBox : public TextBox
{
public:
    CodeBox(QString text, BoxStyle style, QString id, int line);
    std::shared_ptr<TextBox> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // CODEBOX_H
