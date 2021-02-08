#pragma once

#include "markdownBaseListener.h"
#include "formatetext.h"

#include <QPainter>

class MarkdownListenerClass: public markdownBaseListener {
public:
    MarkdownListenerClass(QPainter& painter, QRect rect, QString id, double linespacing);

    void enterMarkdown(markdownParser::MarkdownContext *ctx) override;
    void exitMarkdown(markdownParser::MarkdownContext *ctx) override;

    void enterText_decorated(markdownParser::Text_decoratedContext *ctx) override;
    void exitText_decorated(markdownParser::Text_decoratedContext *ctx) override;

    void enterText_bold(markdownParser::Text_boldContext *ctx) override;
    void exitText_bold(markdownParser::Text_boldContext *ctx) override;

    void enterText_italic(markdownParser::Text_italicContext *ctx) override;
    void exitText_italic(markdownParser::Text_italicContext *ctx) override;

    void enterText_plain(markdownParser::Text_plainContext *ctx) override;
    void exitText_plain(markdownParser::Text_plainContext *ctx) override;

    void enterLatex(markdownParser::LatexContext *ctx) override;
    void exitLatex(markdownParser::LatexContext *ctx) override;

    void enterNew_line(markdownParser::New_lineContext * /*ctx*/) override;
    void enterItem(markdownParser::ItemContext * /*ctx*/) override;
    void enterItemize(markdownParser::ItemizeContext * /*ctx*/) override;
    void exitItemize(markdownParser::ItemizeContext * /*ctx*/) override;

    void setPainter(QPainter& painter);

private:
    QPainter& mPainter;
    QRect mRect;
    FormateText mFormateText;
    
};
