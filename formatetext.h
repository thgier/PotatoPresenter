#ifndef FORMATETEXT_H
#define FORMATETEXT_H

#include <QString>
#include <QPainter>
#include <vector>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

class FormateText
{
public:
    FormateText(QFontMetrics metrics, QRect rect);
    void drawText(QString text, QPainter& painter);
    std::vector<int> getLinePosition() const;
    void drawNewLine();
    void drawItem(QPainter& painter);
private:
    QFontMetrics mMetrics;
    QRect mRect;
    int mLineStart;
    int mLinewidth;
    std::vector<int> mLinePositions;
    int mLineN = 0;
};

#endif // FORMATETEXT_H
