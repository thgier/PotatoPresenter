#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "box.h"
#include <QString>
#include <QSize>
#include "property.h"
#include "drawtext.h"
#include "formatetext.h"

class TextField: public Box
{
public:
    TextField(QString text, BoxRect rect, QString id);
    QString mText;
    QString Text();
    void drawContent(QPainter& painter) override;
};

#endif // TEXTFIELD_H
