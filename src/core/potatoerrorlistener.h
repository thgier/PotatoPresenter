/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef POTATOERRORLISTENER_H
#define POTATOERRORLISTENER_H

#include "antlr4-runtime.h"
#include "potatoLexer.h"
#include "potatoParser.h"

#include <QString>

struct SyntaxError {
    size_t line, column;
    QString message;
};

class PotatoErrorListener : public antlr4::BaseErrorListener
{
public:
    PotatoErrorListener();
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
          const std::string &msg, std::exception_ptr e) override;
    bool success();
    SyntaxError error();
//    std::vector<std::string>

private:
    SyntaxError mError;
    bool mSuccess = true;

};

#endif // POTATOERRORLISTENER_H
