#include "plaintextbox.h"
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
    PainterTransformScope scope(this, painter);
    painter.setPen(mStyle.mColor);
    auto const linespacing = painter.fontMetrics().leading() + mStyle.mLineSpacing * painter.fontMetrics().lineSpacing();
    QTextLayout textLayout(text);
    textLayout.setTextOption(QTextOption(mStyle.mAlignment));
    textLayout.setFont(painter.font());
    textLayout.setCacheEnabled(true);
    textLayout.beginLayout();
    double y = 0;
    while (1) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid()){
            break;
        }
        line.setLineWidth(geometry().rect().width());
        line.setPosition(QPointF(0, y));
        y += linespacing;
    }
    textLayout.endLayout();
    textLayout.draw(&painter, geometry().rect().topLeft());
}
