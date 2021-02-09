#include "markdownListenerClass.h"

MarkdownListenerClass::MarkdownListenerClass(QPainter &painter, QRect rect, QString id, double linespacing)
    : markdownBaseListener()
    , mPainter(painter)
    , mRect(rect)
    , mFormateText(painter.fontMetrics(), rect, id, linespacing)
{

}

void MarkdownListenerClass::enterMarkdown(markdownParser::MarkdownContext *ctx) {}
void MarkdownListenerClass::exitMarkdown(markdownParser::MarkdownContext *ctx) {}

void MarkdownListenerClass::enterText_decorated(markdownParser::Text_decoratedContext *ctx) {}
void MarkdownListenerClass::exitText_decorated(markdownParser::Text_decoratedContext *ctx) {}

void MarkdownListenerClass::enterText_bold(markdownParser::Text_boldContext *ctx) {
    auto font = mPainter.font();
    font.setBold(true);
    mPainter.setFont(font);
}
void MarkdownListenerClass::exitText_bold(markdownParser::Text_boldContext *ctx) {
    auto font = mPainter.font();
    font.setBold(false);
    mPainter.setFont(font);
}

void MarkdownListenerClass::enterText_italic(markdownParser::Text_italicContext *ctx) {
    auto font = mPainter.font();
    font.setItalic(true);
    mPainter.setFont(font);
}
void MarkdownListenerClass::exitText_italic(markdownParser::Text_italicContext *ctx) {
    auto font = mPainter.font();
    font.setItalic(false);
    mPainter.setFont(font);
}

void MarkdownListenerClass::enterText_plain(markdownParser::Text_plainContext *ctx) {
    mFormateText.drawText(QString::fromStdString(ctx->getText()), mPainter);
}
void MarkdownListenerClass::exitText_plain(markdownParser::Text_plainContext *ctx) {}

void MarkdownListenerClass::enterLatex(markdownParser::LatexContext *ctx) {
    mFormateText.setLatexNext(true);
}

void MarkdownListenerClass::exitLatex(markdownParser::LatexContext *ctx) {
    mFormateText.setLatexNext(false);
}

void MarkdownListenerClass::enterNew_line(markdownParser::New_lineContext * /*ctx*/) {
    mFormateText.drawNewLine();
}

void MarkdownListenerClass::enterItem(markdownParser::ItemContext *) {
    mFormateText.drawItem(mPainter);
}

void MarkdownListenerClass::enterItemize(markdownParser::ItemizeContext *) {
    mFormateText.drawNewHalfLine();
}

void MarkdownListenerClass::exitItemize(markdownParser::ItemizeContext *) {
    mFormateText.drawNewHalfLine();
}

void MarkdownListenerClass::enterItem_second(markdownParser::Item_secondContext * /*ctx*/) {
    mFormateText.drawItemSecond(mPainter);
}
