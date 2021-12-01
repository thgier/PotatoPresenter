/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include "markdownBaseListener.h"
#include "box.h"
#include "textbox.h"
#include "latexcachemanager.h"

#include <QPainter>
#include <QTextLayout>
#include <QSvgRenderer>

struct FormatStack {
    QVector<QTextLayout::FormatRange> mVector;
    int mStackPos = -1;
    void push(QTextLayout::FormatRange formatRange) {
        mVector.append(formatRange);
        mStackPos = mVector.length() - 1;
    }
    void push(int start, QTextCharFormat format) {
        QTextLayout::FormatRange newFormatRange {start, start, format};
        mVector.append(newFormatRange);
        mStackPos = mVector.length() - 1;
    }
    void pop(int end) {
        mVector[mStackPos].length = end - mVector[mStackPos].start;
        mStackPos--;
    }
    void clear() {
        mVector.clear();
        mStackPos = -1;
    }
};

struct MapSvg{
    int mTextPosition;
    std::shared_ptr<QSvgRenderer> mSvg;
    QSizeF mSize;
};


class MarkdownFormatVisitor: public markdownBaseListener {
public:
    MarkdownFormatVisitor(QPainter& painter, QRect const& rect, BoxStyle const& style);

    void enterText_plain(markdownParser::Text_plainContext *ctx) override;

    void enterText_bold(markdownParser::Text_boldContext * /*ctx*/) override;
    void exitText_bold(markdownParser::Text_boldContext * /*ctx*/) override;

    void enterText_italic(markdownParser::Text_italicContext * ctx) override;
    void exitText_italic(markdownParser::Text_italicContext * /*ctx*/) override;

    void enterText_marked(markdownParser::Text_markedContext * /*ctx*/) override;
    void exitText_marked(markdownParser::Text_markedContext * /*ctx*/) override;

    void enterLatex(markdownParser::LatexContext *ctx) override;
    void exitLatex(markdownParser::LatexContext *ctx) override;
    void enterLatex_next_line(markdownParser::Latex_next_lineContext *ctx) override;
    void exitLatex_next_line(markdownParser::Latex_next_lineContext *ctx) override;

    void exitParagraph(markdownParser::ParagraphContext * /*ctx*/) override;

    void enterItem(markdownParser::ItemContext * /*ctx*/) override;
    void enterItem_second(markdownParser::Item_secondContext * /*ctx*/) override;
    void enterEnum_item(markdownParser::Enum_itemContext *ctx) override;
    void enterEnum_item_second(markdownParser::Enum_item_secondContext *ctx) override;

    TextBoundings textBoundings() const;

    void setLatexConversionFlags(ConversionType latexConversionType);

private:
    void addXToPosition(qreal dx);
    void addYToPosition(qreal dy);
    void newLine();
    void drawFormulasInParagraph(QTextLayout &layout);
    MapSvg loadSvg(QString mathExpression, int start);

private:
    QPainter& mPainter;
    QRect const mRect;
    struct {
        FormatStack mStack;
        QString mText;
    } mCurrentParagraph;
    QPointF mStartOfLine;
    double const mLineSpacing;
    bool mDrawPlainText = true;
    BoxStyle mBoxStyle;
    std::vector<MapSvg> mMapSvgs;

    TextBoundings mTextBoundings;
    ConversionType mLatexConversionType = NoBreak;

};

