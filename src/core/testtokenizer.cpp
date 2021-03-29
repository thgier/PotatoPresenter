/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

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
    QTest::newRow("first test") << QByteArray("\\slide first page") << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Text, "first page", 1}};
    QTest::newRow("split command") << QByteArray("\\text hallo\n\\image du")
                                   << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::Text, "hallo", 1}
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
                               << QVector<Token>{Token{Token::Kind::EndOfFile, "", 1}};
    QTest::newRow("multiline") << QByteArray("\\text ich bin eine \n neue Zeile") << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::MultiLineText, "ich bin eine \n neue Zeile", 1}};
    QTest::newRow("multiline paragraph") << QByteArray("\\text ich bin eine \n\n neue Zeile") << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::MultiLineText, "ich bin eine \n\n neue Zeile", 1}};
    QTest::newRow("next line") << QByteArray("\\text hallo\n\\slide du")
                               << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::Text, "hallo", 1},
                                Token{Token::Kind::Command, "\\slide", 2}, Token{Token::Kind::Text, "du", 2}};
    QTest::newRow("next line after command") << QByteArray("\\text\n\\slide du")
                               << QVector<Token>{Token{Token::Kind::Command, "\\text", 1},
                                  Token{Token::Kind::Command, "\\slide", 2}, Token{Token::Kind::Text, "du", 2}};
    QTest::newRow("next line with text after command") << QByteArray("\\text\ndu")
                                             << QVector<Token>{Token{Token::Kind::Command, "\\text", 1}, Token{Token::Kind::MultiLineText, "du", 1}};
    QTest::newRow("space") << QByteArray("\\slide first \n\\text title")
                                             << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Text, "first", 1},
                                                Token{Token::Kind::Command, "\\text", 2}, Token{Token::Kind::Text, "title", 2}};
    QTest::newRow("argument") << QByteArray("\\slide[opacity:0.5]")
                           << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Argument, "opacity", 1},
                            Token{Token::Kind::ArgumentValue, "0.5", 1}};
    QTest::newRow("slideclass") << QByteArray("\\slide[class:titlepage]")
                              << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Argument, "class", 1},
                                 Token{Token::Kind::ArgumentValue, "titlepage", 1}};
    QTest::newRow("multiple arguments") << QByteArray("\\slide[opacity:0.5; color: red] Hello")
                               << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Argument, "opacity", 1},
                                    Token{Token::Kind::ArgumentValue, "0.5", 1}, Token{Token::Kind::Argument, "color", 1},
                                  Token{Token::Kind::ArgumentValue, "red", 1}, Token{Token::Kind::Text, "Hello", 1}};
    QTest::newRow("multiple arguments with command") << QByteArray("\\slide[opacity:0.5; color: red]\n\\text")
                               << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Argument, "opacity", 1},
                                  Token{Token::Kind::ArgumentValue, "0.5", 1}, Token{Token::Kind::Argument, "color", 1},
                                  Token{Token::Kind::ArgumentValue, "red", 1}, Token{Token::Kind::Command, "\\text", 2}};
    QTest::newRow("missing argument") << QByteArray("\\slide[]")
                                                     << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::EndOfFile, "", 1}};
    QTest::newRow("missing value") << QByteArray("\\slide[opacity]")
                                      << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Argument, "opacity", 1}};
    QTest::newRow("missing value with :") << QByteArray("\\slide[opacity:]")
                                      << QVector<Token>{Token{Token::Kind::Command, "\\slide", 1}, Token{Token::Kind::Argument, "opacity", 1}};
}

