#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "textbox.h"
#include <QString>
#include <QSize>

class MarkdownTextBox: public TextBox
{
public:
    MarkdownTextBox(QString text, BoxStyle style, QString id, int line);
    std::shared_ptr<TextBox> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // TEXTFIELD_H
