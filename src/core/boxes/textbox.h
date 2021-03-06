#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "box.h"
#include <QString>
#include <QSize>

class TextBox: public Box
{
public:
    TextBox(QString text, BoxStyle style, QString id, int line);
    QString mText;
    QString Text();
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // TEXTFIELD_H
