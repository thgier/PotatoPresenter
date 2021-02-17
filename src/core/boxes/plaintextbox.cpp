#include "plaintextbox.h"
#include "formattedTextRenderer.h"
#include <QFontMetrics>
#include <QTextLayout>
#include <QTextDocument>

PlainTextBox::PlainTextBox(QString text, BoxGeometry rect, QString id)
    : Box(rect, id), mText(text)
{
}

QString PlainTextBox::Text(){
    return mText;
}

void PlainTextBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    auto const text = substituteVariables(mText, variables);
    startDraw(painter);
    painter.setPen(mStyle.mColor);
    auto textRenderer = FormattedTextRenderer(painter.fontMetrics(), geometry().rect(), id(), mStyle.mLineSpacing);
    textRenderer.drawText(text, painter);
    endDraw(painter);
}
