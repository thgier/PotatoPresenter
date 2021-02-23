#include "textbox.h"

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

TextBox::TextBox(QString text, BoxGeometry rect, QString id)
    : Box(rect, id), mText(text)
{
}

QString TextBox::Text(){
    return mText;
}

void TextBox::drawContent(QPainter& painter, std::map<QString, QString> variables) {
    auto const text = substituteVariables(mText, variables);
    PainterTransformScope scope(this, painter);
    painter.setPen(mStyle.mColor);

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


