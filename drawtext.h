#ifndef DRAWTEXT_H
#define DRAWTEXT_H
#include "property.h"
#include <vector>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QPainter>
#include "formatetext.h"


class DrawText
{
public:
    DrawText(QString text, QPainter& painter, QRect rect, int id);
    void makePropertyList();
    std::vector<Property> getProberties(QRegularExpression re, fontChange changeStart, fontChange changeEnd);
    std::vector<Property> getProberties(QRegularExpression re, fontChange changeStart);
    void drawWord(QPainter& painter);
    void drawProperty(fontChange change, QString text, QPainter& painter);
private:
    std::vector<Property> mProp;
    int mCharNumber;
    QString mText;
    FormateText mFormateText;
};

#endif // DRAWTEXT_H
