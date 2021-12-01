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
    parser.removeErrorListeners(); // remove ConsoleErrorListener
    MarkdownErrorListener errorListener;
    parser.addErrorListener(&errorListener); // add ours
    antlr4::tree::ParseTree *tree = parser.markdown();
    qInfo() << "generated tree: " << QString::fromStdString(tree->toStringTree(&parser));
    QVERIFY(errorListener.success());
}

void MarkdownTest::testMarkdown_data(){
    QTest::addColumn<QString>("inputText");
    QTest::newRow("word") << "Hello";
    QTest::newRow("bold") << "**Hello**";
    QTest::newRow("bold 2") << "fdfds **Hello**";
    QTest::newRow("bold 3") << "**Hello** rerw";

    QTest::newRow("italic") << "__Hello__";
    QTest::newRow("italic 2") << "fdfds __Hello__";
    QTest::newRow("italic 3") << "__Hello__ rerw";

    QTest::newRow("marked") << "*Hello*";
    QTest::newRow("marked 2") << "fdfds *Hello*";
    QTest::newRow("marked 3") << "*Hello* rerw";

    QTest::newRow("itemization") << "And use them: \n* The tomato is a %{tomato}\n* The date is %{date}\n* The current pagenumber is %{pagenumber} of %{totalpages}";
    QTest::newRow("itemization at start") << "* The tomato is a %{tomato}\n* The date is %{date}\n* The current pagenumber is %{pagenumber} of %{totalpages}";
    QTest::newRow("itemization with text at end") << "* The tomato is a %{tomato}\n* The date is %{date}\nThe current pagenumber is %{pagenumber} of %{totalpages}";
    QTest::newRow("itemization subitems") << "* The tomato is a %{tomato}\n    * The date is %{date}\nThe current pagenumber is %{pagenumber} of %{totalpages}";

    QTest::newRow("enumeration") << "And use them: \n1. The tomato is a %{tomato}\n2. The date is %{date}\n    1. The current pagenumber is %{pagenumber} of %{totalpages}";

    QTest::newRow("Formula inline") << "And use them $\\pi$ dsds";
    QTest::newRow("Formula next line") << "And use them \n$$\\pi$$\n dsds";
    QTest::newRow("Formula next line 2") << "And use them \n$$\\pi$$";
    QTest::newRow("Formula next line with newlines") << "$$\\pi$$\n\nHello";

}


