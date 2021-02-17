#ifndef FORMATETEXT_H
#define FORMATETEXT_H

#include <QString>
#include <QPainter>
#include <vector>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QSvgRenderer>

class FormattedTextRenderer
{
public:
    enum LatexMode {
        inlineMode,
        displayMode
    };
    FormattedTextRenderer(QFontMetrics metrics, QRect rect, QString id, double linespacing);
    void drawText(QString text, QPainter& painter);
    void drawNewLine();
    void drawPartOfLine(double partOfLine);
    void drawItem(QPainter& painter);
    void drawItemSecond(QPainter& painter);
    void drawEnumItem(QString number, QPainter& painter);
    void drawEnumItemSecond(QString number, QPainter& painter);
    void drawTeX(QString mathExpression, FormattedTextRenderer::LatexMode mode, QPainter& painter);

private:
    void drawSvg(std::shared_ptr<QSvgRenderer> image, FormattedTextRenderer::LatexMode mode, QPainter& painter);

    QFontMetrics mMetrics;
    QRect mRect;
    int mLineStart;
    double mLineY;
    int mLinewidth;
    double mLinespacing;
    QString mIdBox;
    std::vector<double> getLinePosition() const;
};

#endif // FORMATETEXT_H
