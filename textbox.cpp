#include "textbox.h"

#include <QDebug>
#include<QGraphicsTextItem>
#include<QRegularExpression>
#include <vector>
#include<QMargins>

TextBox::TextBox(QString text, BoxGeometry rect, QString id)
    : Box(rect, id), mText(text)
{
}

QString TextBox::Text(){
    return mText;
}

void TextBox::drawContent(QPainter& painter) {
    mText = substituteVariables(mText, mVariables);
    startDraw(painter);
    auto font = QFont(mStyle.mFont);
    font.setPixelSize(mStyle.mFontSize);
    painter.setFont(font);
    painter.setPen(mStyle.mColor);
    auto draw = DrawText(mText, painter, geometry().rect(), id());
    draw.drawWord(painter);
    endDraw(painter);
}


