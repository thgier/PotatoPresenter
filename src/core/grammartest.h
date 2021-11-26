/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef GRAMMARTEST_H
#define GRAMMARTEST_H

#include <QtTest/QTest>

class GrammarTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testGrammar();
    void testGrammar_data();
};

#endif // GRAMMARTEST_H
