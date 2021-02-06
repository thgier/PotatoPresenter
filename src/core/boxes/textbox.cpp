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

void TextBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    auto const text = substituteVariables(mText, variables);
    startDraw(painter);
    painter.setPen(mStyle.mColor);
    auto draw = DrawText(text, painter, geometry().rect(), id(), mStyle.mLineSpacing);
    draw.drawWord(painter);
    endDraw(painter);
}


