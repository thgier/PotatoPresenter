/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "grammartest.h"

#include "potatoParser.h"
#include "potatoLexer.h"
#include "potatoerrorlistener.h"

#include<QtDebug>
#include<QBuffer>
#include <memory>
#include <string>

QTEST_MAIN(GrammarTest)

void GrammarTest::testGrammar() {
    QFETCH(QString, inputText);
    qInfo() << "Test Text: " << inputText;

    std::istringstream str(inputText.toStdString());
    antlr4::ANTLRInputStream input(str);
    potatoLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    potatoParser parser(&tokens);
    parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);
    parser.removeErrorListeners(); // remove ConsoleErrorListener
    PotatoErrorListener errorListener;
    parser.addErrorListener(&errorListener); // add ours
    antlr4::tree::ParseTree *tree = parser.potato();
    qInfo() << "generated tree: " << QString::fromStdString(tree->toStringTree(&parser));
    QVERIFY(errorListener.success());
}

void GrammarTest::testGrammar_data(){
    QTest::addColumn<QString>("inputText");
    QTest::newRow("only slide") << "\\slide first page";
    QTest::newRow("proberty") << "\\slide[class:titlepage] first page";
    QTest::newRow("proberty list") << "\\text[class:body; font-size: 60; opacity:0.8] first page";
    QTest::newRow("proberty list with space") << "\\body[id:body2; font-size: 60; font: Linux Biolinum; color: #444; line-height: 1.5] first page";
    QTest::newRow("slide with newline") << "\\slide first page\n";
    QTest::newRow("more newline") << "\\slide first page\n\n\n \\image toll";
    QTest::newRow("backslash inline") << "\\slide first \\page\n";
    QTest::newRow("bold") << "\\slide **first** page\n";
    QTest::newRow("italic") << "\\slide _first_ page\n";
    QTest::newRow("more line text") << "\\slide _first_ page\n*dsds*";
    QTest::newRow("title with empty text") << "\\slide hello\n\\title";
    QTest::newRow("empty text") << "\\slide hello \\title\n\body";
    QTest::newRow("colon") << "\\slide hello: \\title";
    QTest::newRow("itemization") << "\\slide hello \body\n  * dsds\n    *dog";
    QTest::newRow("Latex at new line") << "\\slide _first_ page\n\\text\n$\\Rightarrow$";
    QTest::newRow("Code") << "\\code[language: Python]\ndef fibonacci(x):\nif x[-1] < 1000:\n";
    QTest::newRow("brackets") << "\\body \\{text\\}";
    QTest::newRow("brackets new line") << "\\body\n\\{\ntext\n\\}";
    QTest::newRow("brackets new line secons") << "\\body\\{\ntext\n\\}";
    QTest::newRow("space") << "\\body[value: 30]\n * Cool";
    QTest::newRow("divided property list") << "\\image[\nborder: 1px solid\n]\nimages/createSvg.png \title";
    QTest::newRow("command with property") << "\\title[text-align: center]\n\\body Click here to choose a template: ";
    QTest::newRow("command with property") << "\\title[text-align: center; ]";
}


