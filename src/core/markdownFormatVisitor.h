#pragma once

#include "markdownBaseListener.h"
#include "formattedTextRenderer.h"

#include <QPainter>

class MarkdownFormatVisitor: public markdownBaseListener {
public:
    MarkdownFormatVisitor(QPainter& painter, QRect rect, QString id, double linespacing);

    void enterText_plain(markdownParser::Text_plainContext *ctx);

    void enterText_bold(markdownParser::Text_boldContext * /*ctx*/) override;
    void exitText_bold(markdownParser::Text_boldContext * /*ctx*/) override;

    void enterText_italic(markdownParser::Text_italicContext * /*ctx*/) override;
    void exitText_italic(markdownParser::Text_italicContext * /*ctx*/) override;

    void enterLatex(markdownParser::LatexContext *ctx) override;
    void exitLatex(markdownParser::LatexContext *ctx) override;
    void enterLatex_next_line(markdownParser::Latex_next_lineContext *ctx) override;
    void exitLatex_next_line(markdownParser::Latex_next_lineContext *ctx) override;

    void enterNew_line(markdownParser::New_lineContext * /*ctx*/) override;

    void enterList(markdownParser::ListContext * /*ctx*/) override;
    void enterItem(markdownParser::ItemContext * /*ctx*/) override;
    void exitItemize(markdownParser::ItemizeContext * /*ctx*/) override;
    void enterItem_second(markdownParser::Item_secondContext * /*ctx*/) override;
    void enterEnum_item(markdownParser::Enum_itemContext *ctx) override;
    void enterEnum_item_second(markdownParser::Enum_item_secondContext *ctx) override;

    void setPainter(QPainter& painter);

private:
    QPainter& mPainter;
    QRect mRect;
    FormattedTextRenderer mFormateText;
    bool mDrawTextPlain = true;
    
};
