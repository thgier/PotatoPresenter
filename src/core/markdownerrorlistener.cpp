/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "markdownerrorlistener.h"

MarkdownErrorListener::MarkdownErrorListener()
{

}

void MarkdownErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
                      const std::string &msg, std::exception_ptr e) {
    mError = SyntaxError {line, charPositionInLine, msg};
    mSuccess = false;
}

bool MarkdownErrorListener::success() {
    return mSuccess;
}
