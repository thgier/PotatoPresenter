#ifndef TITLEFIELD_H
#define TITLEFIELD_H

#include "textfield.h"
#include <QString>

class TitleField : public TextField
{
public:
    TitleField(QString title, QRect rect);
    QString mText;
};

#endif // TITLEFIELD_H
