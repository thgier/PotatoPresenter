#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "box.h"
#include <QString>
#include <QSize>
#include "textproperty.h"
#include "drawtext.h"
#include "formatetext.h"

class TextBox: public Box
{
public:
    TextBox(QString text, BoxGeometry rect, QString id);
    QString mText;
    QString Text();
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // TEXTFIELD_H
