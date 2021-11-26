/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "potatoerrorlistener.h"

#include <QString>
#include <algorithm>

PotatoErrorListener::PotatoErrorListener()
{

}


void PotatoErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
                      const std::string &msg, std::exception_ptr e) {
    mSuccess = false;
    std::vector<std::string> rules = static_cast<antlr4::Parser*>(recognizer)->getRuleInvocationStack();
    auto message = QString("");
    //::fromStdString(rules.front()) + " " + QString::fromStdString(offendingSymbol->getText());
    if(rules.front() == "property_list") {
        message.append(" Properties must be in the format [property: value; property: value; etc].");
        if(offendingSymbol->getText() == "\\") {
            message.append(" Missing value?");
        }
        if(offendingSymbol->getText() == ":") {
            message.append(" Missing property?");
        }
    }
    if(rules.front() == "property_entry") {
        message.append(" Properties must be in the format [property: value; property: value; etc].");
        if(offendingSymbol->getText() == "\\") {
            message.append(" Missing ']' or ':' value?");
        }

    }
    if(rules.front() == "box") {
        message.append("A command must be in the form \\command [property list] paragraph.");
        if(offendingSymbol->getText() == "\\") {
            message.append(" Missing newline for command?");
        }
        if(offendingSymbol->getText() == "}") {
            message.append(" Missing '\\}'?");
        }
    }
    if(rules.front() == "command") {
        message.append("A command must be in the form \\command [property list] paragraph.");
        if(offendingSymbol->getText() == "\\") {
            message.append(" Missing newline for command?");
        }
        if(offendingSymbol->getText() == " ") {
            message.append(" Missing command? Space is permited behind '\\'.");
        }
        if(offendingSymbol->getText() == "{") {
            message.append(" Missing '\\}'?");
        }
    }
    if(rules.front() == "potato") {
        message.append("Missing Input or '\\'?");
    }

    mError = SyntaxError {line, charPositionInLine, message};
}

bool PotatoErrorListener::success() {
    return mSuccess;
}

SyntaxError PotatoErrorListener::error() {
    return mError;
}

