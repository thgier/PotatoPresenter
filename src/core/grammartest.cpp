#include "grammartest.h"

#include "antlr4-runtime.h"
#include "potatoLexer.h"
#include "potatoParser.h"

#include<QtDebug>
#include<QBuffer>
#include <memory>
#include <string>

QTEST_MAIN(GrammarTest)

void GrammarTest::testGrammar() {
    QFETCH(QString, inputText);
    QFETCH(QString, elements);
    qInfo() << "Test Text: " << inputText;

    antlr4::ANTLRInputStream input(inputText.toStdString());
    potatoLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    potatoParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.potato();

    auto const treeString = QString::fromStdString(tree->toStringTree(&parser));

    qInfo() << "Test Output: " << treeString;

    QCOMPARE(elements, treeString);
}

void GrammarTest::testGrammar_data(){
    QTest::addColumn<QString>("inputText");
    QTest::addColumn<QString>("elements");
    QTest::newRow("first test") << "\\slide first page\n" << "(potato (box (command \\ slide  ) (paragraph (text (text_colon first   page)) \n)) <EOF>)";
  }


