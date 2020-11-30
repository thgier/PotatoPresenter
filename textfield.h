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
    TextField(QString text, QRect rect, int id);
    QString mText;
    QString Text();
    void drawContent(QPainter& painter) override;
private:
    int mCharNumber;
};

#endif // TEXTFIELD_H
