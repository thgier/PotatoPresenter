#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include <vector>
#include <QTextLayout>
#include <abstracthighlighter.h>
#include <repository.h>
#include <theme.h>

class CodeHighlighter : private KSyntaxHighlighting::AbstractHighlighter
{
public:
    CodeHighlighter(QString language);
    std::vector<QVector<QTextLayout::FormatRange>> highlightLines(QStringList list);

protected:
    void applyFormat(int  offset, int  length, const KSyntaxHighlighting::Format&  format) override;

private:
    std::vector<QVector<QTextLayout::FormatRange>> mFormats;
    int LineNumber = 0;
    KSyntaxHighlighting::Theme mTheme;
};

#endif // CODEHIGHLIGHTER_H
