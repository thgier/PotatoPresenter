#ifndef FORMATETEXT_H
#define FORMATETEXT_H

#include <QString>
#include <QPainter>
#include <vector>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

//class EquationCacheManager {

//};

//EquationCacheManager& cacheManager()
//{
//    static EquationCacheManager instance;
//    return instance;
//}

//auto image = cacheManager().getCachedImage(...);

class FormateText
{
public:
    FormateText(QFontMetrics metrics, QRect rect, int id);
    void drawText(QString text, QPainter& painter);
    std::vector<int> getLinePosition() const;
    void drawNewLine();
    void drawItem(QPainter& painter);
    void drawTeX(QString mathExpression, QPainter& painter);
//signals:
//    void mathFormular(QString mathExpression);
private:
    QFontMetrics mMetrics;
    QRect mRect;
    int mLineStart;
    int mLinewidth;
    std::vector<int> mLinePositions;
    int mLineN = 0;
    int mIdBox;
};

#endif // FORMATETEXT_H
