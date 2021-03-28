/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "codehighlighter.h"
#include <format.h>
#include <state.h>
#include <definition.h>
#include <QDebug>

CodeHighlighter::CodeHighlighter(QString language)
{
    static auto repo = std::make_shared<KSyntaxHighlighting::Repository>();
    mTheme = repo->defaultTheme();
    setDefinition(repo->definitionForName(language));
    qInfo() << "language is valid" << repo->definitionForName(language).isValid();
}

void CodeHighlighter::applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) {
    QTextCharFormat charFormat;
    charFormat.setForeground(format.textColor(mTheme));
    if(format.isBold(mTheme)) {
        charFormat.setFontWeight(QFont::Weight::Bold);
    }
    if(format.isItalic(mTheme)) {
        charFormat.setFontItalic(true);
    }
    mFormats[LineNumber].push_back(QTextLayout::FormatRange{offset, length, charFormat});
}

std::vector<QVector<QTextLayout::FormatRange> > CodeHighlighter::highlightLines(QStringList list) {
    mFormats.clear();
    mFormats.resize(list.size());
    KSyntaxHighlighting::State state;
    for(auto const& line: list) {
        state = highlightLine(line, state);
        LineNumber++;
    }
    return mFormats;
}
