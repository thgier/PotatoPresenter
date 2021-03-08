#include "plaintextbox.h"
#include <QFontMetrics>
#include <QTextLayout>
#include <QTextDocument>

PlainTextBox::PlainTextBox(QString text, BoxStyle style, QString id, int line)
    : TextBox(text, style, id, line)
{
}

std::shared_ptr<TextBox> PlainTextBox::clone() {
    return std::make_shared<PlainTextBox>(*this);
}

void PlainTextBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    auto const text = substituteVariables(mText, variables);
    PainterTransformScope scope(this, painter);
    painter.setPen(mStyle.color());
    auto const linespacing = painter.fontMetrics().leading() + mStyle.linespacing() * painter.fontMetrics().lineSpacing();
    QTextLayout textLayout(text);
    textLayout.setTextOption(QTextOption(mStyle.alignment()));
    textLayout.setFont(painter.font());
    textLayout.setCacheEnabled(true);
    textLayout.beginLayout();
    double y = 0;
    while (1) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid()){
            break;
        }
        line.setLineWidth(geometry().width());
        line.setPosition(QPointF(0, y));
        y += linespacing;
    }
    textLayout.endLayout();
    textLayout.draw(&painter, geometry().topLeft());
}
