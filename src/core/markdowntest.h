#ifndef MARKDOWNTEST_H
#define MARKDOWNTEST_H

#include <QtTest/QTest>

class MarkdownTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testMarkdown();
    void testMarkdown_data();
};

#endif // MARKDOWNTEST_H
