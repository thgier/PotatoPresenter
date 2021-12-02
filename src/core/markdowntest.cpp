/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "markdowntest.h"

#include "markdownParser.h"
#include "markdownLexer.h"
#include "markdownerrorlistener.h"

#include<QtDebug>
#include<QBuffer>
#include <memory>
#include <string>

QTEST_MAIN(MarkdownTest)

void MarkdownTest::testMarkdown() {
    QFETCH(QString, inputText);
    qInfo() << "Test Text: " << inputText;

    std::istringstream str(inputText.toStdString());
    antlr4::ANTLRInputStream input(str);
    markdownLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    markdownParser parser(&tokens);
    parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);
    parser.removeErrorListeners(); // remove ConsoleErrorListener
    MarkdownErrorListener errorListener;
    parser.addErrorListener(&errorListener); // add ours
    antlr4::tree::ParseTree *tree = parser.markdown();
    qInfo() << "generated tree: " << QString::fromStdString(tree->toStringTree(&parser));
    QVERIFY(errorListener.success());
}

void MarkdownTest::testMarkdown_data(){
    QTest::addColumn<QString>("inputText");
    QTest::newRow("word") << "Hello\n";
    QTest::newRow("bold") << "**Hello**\n";
    QTest::newRow("bold 2") << "fdfds **Hello**\n";
    QTest::newRow("bold 3") << "**Hello** rerw\n";

    QTest::newRow("italic") << "__Hello__\n";
    QTest::newRow("italic 2") << "fdfds __Hello__\n";
    QTest::newRow("italic 3") << "__Hello__ rerw\n";

    QTest::newRow("marked") << "*Hello*\n";
    QTest::newRow("marked 2") << "fdfds *Hello*\n";
    QTest::newRow("marked 3") << "*Hello* rerw\n";

    QTest::newRow("itemization") << "And use them: \n* The tomato is a %{tomato}\n* The date is %{date}\n* The current pagenumber is %{pagenumber} of %{totalpages}\n";
    QTest::newRow("itemization at start") << "* The tomato is a %{tomato}\n* The date is %{date}\n* The current pagenumber is %{pagenumber} of %{totalpages}\n";
    QTest::newRow("itemization with text at end") << "* The tomato is a %{tomato}\n* The date is %{date}\nThe current pagenumber is %{pagenumber} of %{totalpages}\n";
    QTest::newRow("itemization subitems") << "* The tomato is a %{tomato}\n    * The date is %{date}\nThe current pagenumber is %{pagenumber} of %{totalpages}\n";
    QTest::newRow("itemization subitems 2") << "* jkjk\n    * fdfd\n";

    QTest::newRow("Tab at start of line") << "* jkjk\n    \nfdfd\n";

    QTest::newRow("enumeration") << "And use them: \n1. The tomato is a %{tomato}\n2. The date is %{date}\n    1. The current pagenumber is %{pagenumber} of %{totalpages}\n";

    QTest::newRow("Formula inline") << "And use them $\\pi$ dsds\n";
    QTest::newRow("Formula next line") << "And use them \n$$\\pi$$\n dsds\n";
    QTest::newRow("Formula next line 2") << "And use them \n$$\\pi$$\n";
    QTest::newRow("Formula next line with newlines") << "$$\\pi$$\n\nHello\n";

}


