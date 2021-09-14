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
