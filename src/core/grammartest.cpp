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
    QTest::newRow("slide with newline") << "\\slide first page\n";
    QTest::newRow("more newline") << "\\slide first page\n\n\n \\image toll";
    QTest::newRow("backslash inline") << "\\slide first \\page\n";
    QTest::newRow("bold") << "\\slide **first** page\n";
    QTest::newRow("italic") << "\\slide _first_ page\n";
    QTest::newRow("more line text") << "\\slide _first_ page\n*dsds*";
    QTest::newRow("title with empty text") << "\\slide hello\n\\title";
    QTest::newRow("empty text") << "\\slide hello \\title\n\body";
    QTest::newRow("colon") << "\\slide hello: \title";
    QTest::newRow("itemization") << "\\slide hello \body\n  * dsds\n    *dog";
    QTest::newRow("Latex at new line") << "\\slide _first_ page\n\\text\n$\\Rightarrow$";
    QTest::newRow("Code") << "\\code[language: Python]\ndef fibonacci(x):\nif x[-1] < 1000:\n";
}


