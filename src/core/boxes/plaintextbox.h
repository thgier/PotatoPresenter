#ifndef PLAINTEXTBOX_H
#define PLAINTEXTBOX_H

#include "textbox.h"

class PlainTextBox : public TextBox
{
public:
    PlainTextBox(QString text, BoxStyle style, QString id, int line);
    std::shared_ptr<TextBox> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // PLAINTEXTBOX_H
