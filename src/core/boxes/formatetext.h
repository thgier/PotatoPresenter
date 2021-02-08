#ifndef FORMATETEXT_H
#define FORMATETEXT_H

#include <QString>
#include <QPainter>
#include <vector>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QSvgRenderer>

class FormateText
{
public:
    FormateText(QFontMetrics metrics, QRect rect, QString id, double linespacing);
    void drawText(QString text, QPainter& painter);
    void drawNewLine();
    void drawNewHalfLine();
    void drawItem(QPainter& painter);
    void drawTeX(QString mathExpression, QPainter& painter);
    void drawSvg(std::shared_ptr<QSvgRenderer> image, QPainter& painter);
    void setLatexNext(bool latexNext);
private:
    QFontMetrics mMetrics;
    QRect mRect;
    int mLineStart;
    double mLineY;
    int mLinewidth;
    double mLinespacing;
    QString mIdBox;
    std::vector<double> getLinePosition() const;
    bool mLatexNext = false;
};

#endif // FORMATETEXT_H
