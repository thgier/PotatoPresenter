#include "markdownFormatVisitor.h"

MarkdownFormatVisitor::MarkdownFormatVisitor(QPainter &painter, QRect rect, QString id, double linespacing)
    : markdownBaseListener()
    , mPainter(painter)
    , mRect(rect)
    , mFormateText(painter.fontMetrics(), rect, id, linespacing)
{

}

void MarkdownFormatVisitor::enterText_bold(markdownParser::Text_boldContext * /*ctx*/) {
    auto font = mPainter.font();
    font.setBold(true);
    mPainter.setFont(font);
}
void MarkdownFormatVisitor::exitText_bold(markdownParser::Text_boldContext * /*ctx*/) {
    auto font = mPainter.font();
    font.setBold(false);
    mPainter.setFont(font);
}

void MarkdownFormatVisitor::enterText_italic(markdownParser::Text_italicContext * /*ctx*/) {
    auto font = mPainter.font();
    font.setItalic(true);
    mPainter.setFont(font);
}
void MarkdownFormatVisitor::exitText_italic(markdownParser::Text_italicContext * /*ctx*/) {
    auto font = mPainter.font();
    font.setItalic(false);
    mPainter.setFont(font);
}

void MarkdownFormatVisitor::enterText_plain(markdownParser::Text_plainContext *ctx) {
    if(mDrawTextPlain) {
        mFormateText.drawText(QString::fromStdString(ctx->getText()), mPainter);
    }
}

void MarkdownFormatVisitor::enterLatex(markdownParser::LatexContext *ctx) {
    mFormateText.drawTeX(QString::fromStdString(ctx->text_plain()->getText()), FormattedTextRenderer::LatexMode::inlineMode, mPainter);
    mDrawTextPlain = false;
}

void MarkdownFormatVisitor::exitLatex(markdownParser::LatexContext *) {
    mDrawTextPlain = true;
}

void MarkdownFormatVisitor::enterLatex_next_line(markdownParser::Latex_next_lineContext *ctx) {
    mFormateText.drawTeX(QString::fromStdString(ctx->text_plain()->getText()), FormattedTextRenderer::LatexMode::displayMode, mPainter);
    mDrawTextPlain = false;
}

void MarkdownFormatVisitor::exitLatex_next_line(markdownParser::Latex_next_lineContext *) {
    mDrawTextPlain = true;
}

void MarkdownFormatVisitor::enterNew_line(markdownParser::New_lineContext * /*ctx*/) {
    mFormateText.drawNewLine();
}

void MarkdownFormatVisitor::enterItem(markdownParser::ItemContext *) {
    mFormateText.drawItem(mPainter);
}

void MarkdownFormatVisitor::enterList(markdownParser::ListContext * /*ctx*/) {
    mFormateText.drawNewHalfLine();
}

void MarkdownFormatVisitor::exitItemize(markdownParser::ItemizeContext *) {
    mFormateText.drawNewHalfLine();
}

void MarkdownFormatVisitor::enterItem_second(markdownParser::Item_secondContext * /*ctx*/) {
    mFormateText.drawItemSecond(mPainter);
}

void MarkdownFormatVisitor::enterEnum_item(markdownParser::Enum_itemContext *ctx) {
    mFormateText.drawEnumItem(QString::fromStdString(ctx->INT()->getText()), mPainter);
}

void MarkdownFormatVisitor::enterEnum_item_second(markdownParser::Enum_item_secondContext *ctx) {
    mFormateText.drawEnumItemSecond(QString::fromStdString(ctx->INT()->getText()), mPainter);
}
