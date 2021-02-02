#ifndef DRAWTEXT_H
#define DRAWTEXT_H
#include "textproperty.h"
#include <vector>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QPainter>
#include "formatetext.h"


class DrawText
{
public:
    DrawText(QString text, QPainter& painter, QRect rect, QString id, double linespacing);
    void makePropertyList();
    std::vector<TextProperty> getProberties(QRegularExpression re, fontChange changeStart, fontChange changeEnd);
    std::vector<TextProperty> getProberties(QRegularExpression re, fontChange changeStart);
    void drawWord(QPainter& painter);
    void drawProperty(fontChange change, QString text, QPainter& painter);
private:
    std::vector<TextProperty> mProp;
    int mCharNumber;
    QString mText;
    FormateText mFormateText;
};

#endif // DRAWTEXT_H
