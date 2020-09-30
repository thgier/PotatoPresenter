#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "box.h"
#include <QString>
#include <QSize>
#include "property.h"
#include "drawtext.h"

class TextField: public Box
{
public:
    TextField(QString text, QRect);
    QString mText;
    QString Text();
    void drawContent(QPainter& painter) override;
    int drawText(int x, int y, QString text, QPainter& painter);
    void renderText(QPainter& painter);
    std::vector<Property> getProberties(QRegularExpression re, fontChange change);
private:
    int mCharNumber;
};

#endif // TEXTFIELD_H
