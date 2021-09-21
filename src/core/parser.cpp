/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QCryptographicHash>
#include <charconv>
#include <QDir>
#include <QRegularExpression>
#include <QDate>

#include "parser.h"
#include "antlr4-runtime.h"
#include "potatoLexer.h"
#include "potatoParser.h"
#include "potatoformatvisitor.h"

ParserOutput generateSlides(std::string text, QString directory, bool isTemplate) {
    std::istringstream str(text);
    antlr4::ANTLRInputStream input(str);
    potatoLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    potatoParser parser(&tokens);
    parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);
    antlr4::tree::ParseTree *tree = parser.potato();

    auto listener = PotatoFormatVisitor();
    listener.setDirectory(directory);
    listener.setParseTemplate(isTemplate);
    try {
        auto walker = antlr4::tree::ParseTreeWalker();
        walker.walk(&listener, tree);
        return ParserOutput(listener.slides(), listener.preamble());

    }  catch (ParserError error) {
        return ParserOutput(error);
    }

}
