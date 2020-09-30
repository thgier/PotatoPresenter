#include "bigtextfield.h"

#include <QRect>

BigTextField::BigTextField(QString text)
    : TextField(text)
{
    QRect rect = QRect(0, 50, 200, 20);
    setRect(rect);
}
