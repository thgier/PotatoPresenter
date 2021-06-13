/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef TESTTOKENIZER_H
#define TESTTOKENIZER_H

#include <QtTest/QTest>
#include <QVector>
#include "tokenizer.h"

class TestTokenizer: public QObject
{
    Q_OBJECT
public:
    TestTokenizer();
private:
    Tokenizer mTokenizer;

private slots:
    void initTestCase();
    void tokenTest();
    void tokenTest_data();

};

Q_DECLARE_METATYPE(QVector<Token>);

#endif // TESTTOKENIZER_H
