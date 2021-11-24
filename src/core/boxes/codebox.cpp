/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "codebox.h"
#include <QTextLayout>
#include "codehighlighter.h"

std::shared_ptr<TextBox> CodeBox::clone() {
    return std::make_shared<CodeBox>(*this);
}

void CodeBox::drawContent(QPainter& painter, std::map<QString, QString> const& variables, PresentationRenderHints hints) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    auto const text = substituteVariables(style().text(), variables);
    auto const paragraphs = text.split("\n");
    painter.setPen(mStyle.color());
    auto font = painter.font();
    font.setStyleHint(font.Monospace);
    auto const linespacing = painter.fontMetrics().leading() + style().linespacing() * painter.fontMetrics().lineSpacing();

    CodeHighlighter highlighter(style().language);
    auto const formats = highlighter.highlightLines(paragraphs);

    double y = 0;
    int lineNumber = 0;
    for(auto const& paragraph: paragraphs) {
        QTextLayout textLayout(paragraph);
        textLayout.setFormats(formats[lineNumber]);
        textLayout.setTextOption(QTextOption(mStyle.alignment()));

        textLayout.setFont(painter.font());

        textLayout.beginLayout();
        QTextLine line = textLayout.createLine();
        line.setLineWidth(style().paintableRect().width());
        line.setPosition(QPointF(0, y));
        mTextBoundings.lineBoundingRects.push_back(line.naturalTextRect());
        y += linespacing;
        textLayout.endLayout();

        textLayout.draw(&painter, style().paintableRect().topLeft());
        lineNumber++;
    }
}

