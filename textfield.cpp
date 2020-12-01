#include "textfield.h"

#include <QDebug>
#include<QGraphicsTextItem>
#include<QRegularExpression>
#include <vector>
#include<QMargins>

TextField::TextField(QString text, QRect rect, int id)
    : Box(rect, id), mText(text), mCharNumber{0}
{
}

QString TextField::Text(){
    return mText;
}

void TextField::drawContent(QPainter& painter) {
    auto font = QFont(mFont);
    font.setPixelSize(mFontSize);
    painter.setFont(font);
    auto draw = DrawText(mText, painter, Rect(), id());
    draw.drawWord(painter);
}


