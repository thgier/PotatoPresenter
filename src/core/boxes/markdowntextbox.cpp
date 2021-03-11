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

MarkdownTextBox::MarkdownTextBox(QString text, BoxStyle style, QString id, int line)
    : TextBox(text, style, id, line)
{

}

std::shared_ptr<TextBox> MarkdownTextBox::clone() {
    return std::make_shared<MarkdownTextBox>(*this);
}

void MarkdownTextBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto const text = substituteVariables(mText, variables);

    std::istringstream str(text.toStdString());
    antlr4::ANTLRInputStream input(str);
    markdownLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    markdownParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.markdown();

    auto listener = MarkdownFormatVisitor(painter, geometry().rect(), mStyle);
    auto walker = antlr4::tree::ParseTreeWalker();
    walker.walk(&listener, tree);
}


