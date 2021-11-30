/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "markdownformatvisitor.h"
#include <algorithm>
#include <QCryptographicHash>
#include "textbox.h"

namespace {
void drawItemMarker(QPainter &painter, QPointF position, qreal size, QColor color) {
    painter.save();
    painter.setBrush(color);
    painter.drawEllipse(position, size, size);
    painter.restore();
}

void drawItemCircle(QPainter &painter, QPointF position, qreal size) {
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(position, size, size);
    painter.restore();
}

double drawSvg(std::shared_ptr<QSvgRenderer> image, QPointF position, QPainter& painter){
    if(!image || !image->isValid()){
        return {};
    }
    if(image->defaultSize().width() == 0){
        return {};
    }
    auto const fontSize = painter.font().pixelSize();
    auto const descent = painter.fontMetrics().descent();
    auto const defaultSize = image->defaultSize();
    auto const height = 1.0 * defaultSize.height() / 8.5 * fontSize;
    auto const width = 1.0 * defaultSize.width() / defaultSize.height() * height;
    position.setY(position.y() + descent);
    auto const paintRect = QRectF(position, QSize(width, height));
    image->render(&painter, paintRect);
    return width;
}

QString latexInput(QString const& formula) {
    return "\\documentclass{standalone}\\usepackage{DejaVuSans}\\usepackage[T1]{fontenc}\\usepackage{xcolor}\\usepackage{siunitx}\\usepackage{amsmath}\\usepackage{amssymb}\\usepackage{stmaryrd}\\usepackage{braket}\\begin{document}$"
    + formula +
    "$\\end{document}";
}

void startLatexConversionProcess(std::string const& formula, ConversionType latexConversionType = NoBreak) {
    auto const input = latexInput(QString::fromStdString(formula));
    cacheManager().startConversionProcess(input, latexConversionType);
}

}

MarkdownFormatVisitor::MarkdownFormatVisitor(QPainter &painter, const QRect &rect, const BoxStyle &style)
    : markdownBaseListener()
    , mPainter(painter)
    , mRect(rect)
    , mLineSpacing(painter.fontMetrics().leading() + style.linespacing() * painter.fontMetrics().lineSpacing())
    , mBoxStyle(style)
{

}

void MarkdownFormatVisitor::enterText_bold(markdownParser::Text_boldContext * /*ctx*/) {
    QTextCharFormat format;
    format.setFontWeight(QFont::Weight::Bold);
    mCurrentParagraph.mStack.push(mCurrentParagraph.mText.length(), format);
}

void MarkdownFormatVisitor::exitText_bold(markdownParser::Text_boldContext * /*ctx*/) {
    auto const end = mCurrentParagraph.mText.length();
    mCurrentParagraph.mStack.pop(end);
}

void MarkdownFormatVisitor::enterText_italic(markdownParser::Text_italicContext * /*ctx*/) {
    QTextCharFormat format;
    format.setFontItalic(true);
    mCurrentParagraph.mStack.push(mCurrentParagraph.mText.length(), format);
}

void MarkdownFormatVisitor::exitText_italic(markdownParser::Text_italicContext * /*ctx*/) {
    mCurrentParagraph.mStack.pop(mCurrentParagraph.mText.length());
}

void MarkdownFormatVisitor::enterText_marked(markdownParser::Text_markedContext *) {
    QTextCharFormat format;
    format.setForeground(mBoxStyle.markerColor());
    if(mBoxStyle.markerFontWeight() == FontWeight::bold) {
        format.setFontWeight(QFont::Weight::Bold);
    }
    mCurrentParagraph.mStack.push(mCurrentParagraph.mText.length(), format);
}

void MarkdownFormatVisitor::exitText_marked(markdownParser::Text_markedContext *) {
    mCurrentParagraph.mStack.pop(mCurrentParagraph.mText.length());
}

void MarkdownFormatVisitor::enterText_plain(markdownParser::Text_plainContext *ctx) {
    if(mDrawPlainText) {
        mCurrentParagraph.mText.append(QString::fromStdString(ctx->getText()));
    }
}

void MarkdownFormatVisitor::enterLatex(markdownParser::LatexContext *ctx) {
    int start = mCurrentParagraph.mText.length();
    auto text = QString::fromStdString(ctx->getText());
    text.remove("$");
    auto const svgEntry = loadSvg(text, start);
    if (!svgEntry.mSvg) {
        return;
    }
    mMapSvgs.push_back(svgEntry);
    QTextCharFormat format;
    format.setForeground(Qt::transparent);
    format.setFontWordSpacing(svgEntry.mSize.width() - mPainter.fontMetrics().horizontalAdvance(". "));
    QTextLayout::FormatRange formatrange{mCurrentParagraph.mText.length(), 2, format};
    mCurrentParagraph.mText.append(". ");
    mCurrentParagraph.mStack.push(formatrange);
    mDrawPlainText = false;
}

void MarkdownFormatVisitor::exitLatex(markdownParser::LatexContext *) {
    mDrawPlainText = true;
}

void MarkdownFormatVisitor::enterLatex_next_line(markdownParser::Latex_next_lineContext *ctx) {
    auto mathExpression = QString::fromStdString(ctx->getText());
    mathExpression.remove("$");
    auto const equation = cacheManager().getCachedImage(latexInput(mathExpression));
    switch(equation.status){
    case SvgStatus::Error: {
        QTextCharFormat format;
        format.setForeground(Qt::red);
        mCurrentParagraph.mStack.push(mCurrentParagraph.mText.length(), format);
        mCurrentParagraph.mText += "LaTeX error";
        mCurrentParagraph.mStack.pop(mCurrentParagraph.mText.length());
        break;
    }
    case SvgStatus::NotStarted:
        startLatexConversionProcess(mathExpression.toStdString());
        break;
    case SvgStatus::Pending:
         break;
    case SvgStatus::Success:
        addYToPosition(0.2 * mLineSpacing);

        auto position = mStartOfLine + mRect.topLeft();
        position.setX(position.x() + 7 * mPainter.fontMetrics().xHeight());
        drawSvg(equation.svg, position, mPainter);

        addYToPosition(1.2 * mLineSpacing);
        break;
    }
    mDrawPlainText = false;
}

void MarkdownFormatVisitor::exitLatex_next_line(markdownParser::Latex_next_lineContext *) {
    mDrawPlainText = true;
}

void MarkdownFormatVisitor::enterNew_line(markdownParser::New_lineContext * /*ctx*/) {
}

void MarkdownFormatVisitor::exitParagraph(markdownParser::ParagraphContext * ctx) {
    if(mCurrentParagraph.mText.at(0) == ' ') {
        mCurrentParagraph.mText.remove(0, 1);
    }
    QTextLayout textLayout(mCurrentParagraph.mText);
    textLayout.setTextOption(QTextOption(mBoxStyle.alignment()));
    textLayout.setFont(mPainter.font());
    textLayout.setCacheEnabled(true);
    textLayout.setFormats(mCurrentParagraph.mStack.mVector);
    textLayout.beginLayout();
    while (1) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid()){
            break;
        }
        line.setLineWidth(mRect.width() - mStartOfLine.x());
        line.setPosition(QPointF(mStartOfLine.x(), mStartOfLine.y()));
        mTextBoundings.lineBoundingRects.push_back(line.naturalTextRect());
        newLine();
    }
    if(ctx->new_line().size() > 1) {
        for(auto i = 1; i < int(ctx->new_line().size()); i++)  {
            newLine();
        }
    }
    textLayout.endLayout();
    textLayout.draw(&mPainter, mRect.topLeft());
    mStartOfLine.setX(0);
    mCurrentParagraph.mStack.clear();
    mCurrentParagraph.mText = "";
    drawFormulasInParagraph(textLayout);
}

void MarkdownFormatVisitor::enterItem(markdownParser::ItemContext *) {
    addYToPosition(mPainter.fontMetrics().lineSpacing() * 0.3);
    mStartOfLine.setX(mPainter.fontMetrics().xHeight() * 3);
    auto const markerSize = mPainter.fontMetrics().xHeight() * 0.3;
    auto middleItem = mStartOfLine;
    middleItem.setY(middleItem.y() + mPainter.fontMetrics().height() / 2);
    drawItemMarker(mPainter, mRect.topLeft() + middleItem, markerSize, mBoxStyle.color());
    addXToPosition(2 * markerSize + mPainter.fontMetrics().horizontalAdvance(" "));
}

void MarkdownFormatVisitor::enterList(markdownParser::ListContext * /*ctx*/) {
}

void MarkdownFormatVisitor::exitItemize(markdownParser::ItemizeContext *) {
}

void MarkdownFormatVisitor::enterItem_second(markdownParser::Item_secondContext * /*ctx*/) {
    addYToPosition(mPainter.fontMetrics().lineSpacing() * 0.15);
    mStartOfLine.setX(mPainter.fontMetrics().xHeight() * 5);
    auto const markerSize = mPainter.fontMetrics().xHeight() * 0.25;
    auto middleItem = mStartOfLine;
    middleItem.setY(middleItem.y() + mPainter.fontMetrics().height() / 2);
    drawItemCircle(mPainter, mRect.topLeft() + middleItem, markerSize);
    addXToPosition(2 * markerSize + mPainter.fontMetrics().horizontalAdvance(" "));
}

void MarkdownFormatVisitor::enterEnum_item(markdownParser::Enum_itemContext *ctx) {
    if(!ctx->INT()) {return;}
    mCurrentParagraph.mText += QString::fromStdString(ctx->INT()->getText()).append('.');
    addYToPosition(mPainter.fontMetrics().lineSpacing() * 0.3);
    mStartOfLine.setX(mPainter.fontMetrics().xHeight() * 3);
}

void MarkdownFormatVisitor::enterEnum_item_second(markdownParser::Enum_item_secondContext *ctx) {
    if(!ctx->INT()) {return;}
    mCurrentParagraph.mText += QString::fromStdString(ctx->INT()->getText()) + '.';
    addYToPosition(mPainter.fontMetrics().lineSpacing() * 0.15);
    mStartOfLine.setX(mPainter.fontMetrics().xHeight() * 5);
}

void MarkdownFormatVisitor::addXToPosition(qreal dx) {
    mStartOfLine.setX(mStartOfLine.x() + dx);
}

void MarkdownFormatVisitor::addYToPosition(qreal dy) {
    mStartOfLine.setY(mStartOfLine.y() + dy);
}

void MarkdownFormatVisitor::newLine() {
    addYToPosition(mLineSpacing);
}

void MarkdownFormatVisitor::drawFormulasInParagraph(QTextLayout &layout) {
    for (auto &formula : mMapSvgs) {
        auto const glyphrun = layout.glyphRuns(formula.mTextPosition, 1);
        if(glyphrun.empty()) {
            return;
        }
        auto positions = glyphrun[0].positions();
        if (positions.empty()) {
            return;
        }
        auto position = positions[0];
        position += mRect.topLeft();
        auto const heightIntegral = 0.9 * formula.mSize.height();
        auto const additionalSpace = 0.9 * (heightIntegral - mPainter.fontMetrics().ascent() - mPainter.fontMetrics().descent()) / 2;
        position.setY(position.y() - additionalSpace - mPainter.fontMetrics().ascent());
        formula.mSvg->render(&mPainter, QRectF(position, 0.9 * formula.mSize));
    }
    mMapSvgs.clear();
}

MapSvg MarkdownFormatVisitor::loadSvg(QString mathExpression, int start) {
    auto const input = latexInput(mathExpression).toUtf8();
    auto equation = cacheManager().getCachedImage(input);
    switch(equation.status){
    case SvgStatus::Error: {
        QTextCharFormat format;
        format.setForeground(Qt::red);
        mCurrentParagraph.mStack.push(mCurrentParagraph.mText.length(), format);
        mCurrentParagraph.mText += "LaTeX error";
        mCurrentParagraph.mStack.pop(mCurrentParagraph.mText.length());
        return {};
    }
    case SvgStatus::NotStarted:
        if(mLatexConversionType == BreakUntillFinished) {
            startLatexConversionProcess(mathExpression.toStdString(), ConversionType::BreakUntillFinished);
            equation = cacheManager().getCachedImage(input);
            if(equation.status == Error) {
                return {};
            }
            break;
        }
        else {
            startLatexConversionProcess(mathExpression.toStdString());
            return {};
        }
    case SvgStatus::Pending:
        return {};
    case SvgStatus::Success:
        break;
    }
    auto const defaultSize = equation.svg->defaultSize();
    qInfo() << "default Size" << defaultSize;
    auto const ascent = 6.861476;
    auto const scale = mPainter.fontMetrics().ascent() / ascent;
    auto const height = 1.0 * defaultSize.height() * scale;
    auto const width = 1.0 * defaultSize.width() * scale;
    return {start, equation.svg, QSizeF(width, height)};
}

TextBoundings MarkdownFormatVisitor::textBoundings() const {
    return mTextBoundings;
}

void MarkdownFormatVisitor::setLatexConversionFlags(ConversionType latexConversionType) {
    mLatexConversionType = latexConversionType;
}
