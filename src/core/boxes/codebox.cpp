#include "codebox.h"
#include <QTextLayout>
#include "codehighlighter.h"

CodeBox::CodeBox(QString text, BoxStyle style, QString id, int line)
    : TextBox(text, style, id, line)
{

}

std::shared_ptr<TextBox> CodeBox::clone() {
    return std::make_shared<CodeBox>(*this);
}

void CodeBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto const text = substituteVariables(mText, variables);
    auto const paragraphs = text.split("\n");
    painter.setPen(mStyle.color());
    auto const linespacing = painter.fontMetrics().leading() + mStyle.linespacing() * painter.fontMetrics().lineSpacing();
    CodeHighlighter highlighter(style().language);
    auto const formats = highlighter.highlightLines(paragraphs);
    double y = 0;
    int lineNumber = 0;
    for(auto const& paragraph: paragraphs) {
        QTextLayout textLayout(paragraph);
        textLayout.setFormats(formats[lineNumber]);
        textLayout.setTextOption(QTextOption(mStyle.alignment()));
        auto font = QFont(style().font());
        font.setPixelSize(style().mFontSize.value_or(40));
        textLayout.setFont(font);
        textLayout.beginLayout();
        QTextLine line = textLayout.createLine();
        line.setLineWidth(geometry().width());
        line.setPosition(QPointF(0, y));
        y += linespacing;
        textLayout.endLayout();
        textLayout.draw(&painter, geometry().topLeft());
        lineNumber++;
    }
}

