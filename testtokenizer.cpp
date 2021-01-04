#include <QBuffer>
#include "testtokenizer.h"

QTEST_MAIN(TestTokenizer)

TestTokenizer::TestTokenizer()
{

}

void TestTokenizer::initTestCase()
{

}

void TestTokenizer::tokenTest(){
    QFETCH(QByteArray, inputText);
    QFETCH(QVector<Token>, tokens);
    qInfo() << "Test Text: " << inputText;
    auto input = QBuffer(&inputText);
    mTokenizer.loadInput(&input);
    for(auto const &expectedToken:tokens){
        Token token = mTokenizer.next();
        qInfo() << "expected" << int(expectedToken.mKind)
                   << "got" << int(token.mKind);
        QCOMPARE(token.mKind, expectedToken.mKind);
        QCOMPARE(token.mText, expectedToken.mText);
    }
}

void TestTokenizer::tokenTest_data(){
    QTest::addColumn<QByteArray>("inputText");
    QTest::addColumn<QVector<Token>>("tokens");
    QTest::newRow("first test") << QByteArray("\\frame first page") << QVector<Token>{Token{Token::Kind::Command, "\\frame", 1}, Token{Token::Kind::Text, "first page", 1}};
    QTest::newRow("split command") << QByteArray("\\text hallo \n\\image du")
                                   << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::Text, "hallo ", 1}
                                      ,Token{Token::Kind::Command, "\\image", 2}, Token{Token::Kind::Text, "du", 2}};
    QTest::newRow("two commands") << QByteArray("\\text \\image")
                                   << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::Text, "\\image", 1}};
    QTest::newRow("one word") << QByteArray("hallo")
                                  << QVector<Token>{Token{Token::Kind::Text, "hallo", 1}};
    QTest::newRow("empty text") << QByteArray("\\text ")
                                  << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::EndOfFile, "", 1}};
    QTest::newRow("empty input") << QByteArray("")
                                << QVector<Token>{Token{Token::Kind::EndOfFile, "", 1}};
    QTest::newRow("one space") << QByteArray(" ")
                               << QVector<Token>{Token{Token::Kind::Text, " ", 1}, Token{Token::Kind::EndOfFile, "", 1}};
    QTest::newRow("multiline") << QByteArray("\\text ich bin eine \n neue Zeile") << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::MultiLineText, "ich bin eine \n neue Zeile", 1}};
    QTest::newRow("next line") << QByteArray("\\text hallo\n\\frame du")
                               << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::Text, "hallo", 1},
                                Token{Token::Kind::Command, "\\frame", 2}, Token{Token::Kind::Text, "du", 2}};
    QTest::newRow("next line after command") << QByteArray("\\text\n\\frame du")
                               << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::Text, "", 1},
                                  Token{Token::Kind::Command, "\\frame", 2}, Token{Token::Kind::Text, "du", 2}};
    QTest::newRow("next line with text after command") << QByteArray("\\text\ndu")
                                             << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::MultiLineText, "\ndu", 1}};
    QTest::newRow("space") << QByteArray("\\frame first \n\\text title")
                                             << QVector<Token>{Token{Token::Kind::Command, "\\frame", 1}, Token{Token::Kind::Text, "first ", 1},
                                                Token{Token::Kind::Command, "\\text", 2}, Token{Token::Kind::Text, "title", 2}};
}
