#include "plaintextbox.h"
#include <QFontMetrics>
#include <QTextLayout>
#include <QTextDocument>


std::shared_ptr<TextBox> PlainTextBox::clone() {
    return std::make_shared<PlainTextBox>(*this);
}

void PlainTextBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    auto const text = substituteVariables(mText, variables);
    auto const paragraphs = text.split("\n");

    auto const linespacing = painter.fontMetrics().leading() + mStyle.linespacing() * painter.fontMetrics().lineSpacing();
    double y = 0;
    for(auto const& paragraph: paragraphs) {
        QTextLayout textLayout(paragraph);
        textLayout.setTextOption(QTextOption(mStyle.alignment()));
        textLayout.setFont(painter.font());
        textLayout.setCacheEnabled(true);
        textLayout.beginLayout();
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
}
