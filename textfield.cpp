#include "textfield.h"

#include <QDebug>
#include<QGraphicsTextItem>
#include<QRegularExpression>
#include <vector>
#include<QMargins>

TextField::TextField(QString text, BoxRect rect, QString id)
    : Box(rect, id), mText(text)
{
}

QString TextField::Text(){
    return mText;
}

void TextField::drawContent(QPainter& painter) {
    startDraw(painter);
    auto font = QFont(mFont);
    font.setPixelSize(mFontSize);
    painter.setFont(font);
    painter.setPen(Qt::black);
    auto draw = DrawText(mText, painter, Rect().rect(), id());
    draw.drawWord(painter);
    endDraw(painter);
}


