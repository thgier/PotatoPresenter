/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "markdowntextbox.h"

#include <QDebug>
#include<QGraphicsTextItem>
#include<QRegularExpression>
#include <vector>
#include<QMargins>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "markdownformatvisitor.h"
#include "antlr4-runtime.h"
#include "markdownLexer.h"
#include "markdownParser.h"
#include "markdownformatvisitor.h"

std::shared_ptr<Box> MarkdownTextBox::clone() {
    return std::make_shared<MarkdownTextBox>(*this);
}

void MarkdownTextBox::drawContent(QPainter& painter, const PresentationContext &context, PresentationRenderHints hints) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto text = substituteVariables(style().text(), context.mVariables);
    text.append("\n");

    std::istringstream str(text.toStdString());
    antlr4::ANTLRInputStream input(str);
    markdownLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    markdownParser parser(&tokens);
    parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);
    antlr4::tree::ParseTree *tree = parser.markdown();

    auto const rect = style().paintableRect();
    auto listener = MarkdownFormatVisitor(painter, rect, style());
    if(hints & PresentationRenderHints::NoPreviewRendering) {
        listener.setLatexConversionFlags(BreakUntillFinished);
    }
    auto walker = antlr4::tree::ParseTreeWalker();
    walker.walk(&listener, tree);
    mTextBoundings = listener.textBoundings();
}


