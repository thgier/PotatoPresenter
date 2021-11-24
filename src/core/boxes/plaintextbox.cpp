/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "plaintextbox.h"
#include <QFontMetrics>
#include <QTextLayout>
#include <QTextDocument>

std::shared_ptr<TextBox> PlainTextBox::clone() {
    return std::make_shared<PlainTextBox>(*this);
}

void PlainTextBox::drawContent(QPainter& painter, std::map<QString, QString> const& variables, PresentationRenderHints hints) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    auto const text = substituteVariables(style().text(), variables);
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
            line.setLineWidth(style().paintableRect().width());
            line.setPosition(QPointF(0, y));
            mTextBoundings.lineBoundingRects.push_back(line.naturalTextRect());
            y += linespacing;
        }
        textLayout.endLayout();
        textLayout.draw(&painter, style().paintableRect().topLeft());
    }
}
