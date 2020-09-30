#include "drawtext.h"
#include <QDebug>

DrawText::DrawText(QString text, QPainter& painter, QRect rect)
    :mCharNumber{0}, mText{text}, mFormateText(painter.fontMetrics(), rect)
{
    makePropertyList();
}

std::vector<Property> DrawText::getProberties(QRegularExpression re, fontChange changeStart, fontChange changeEnd) {
    QRegularExpressionMatchIterator i = re.globalMatch(mText);
    std::vector<Property> properties = {};
    while(i.hasNext()){
        auto word = i.next();
        auto text = word.captured(0);
        int start = word.capturedStart();
        int end = word.capturedEnd();
        auto propStart = Property(start, changeStart);
        auto propEnd = Property(end, changeEnd);
        properties.push_back(propStart);
        properties.push_back(propEnd);
    }
    return properties;
}

std::vector<Property> DrawText::getProberties(QRegularExpression re, fontChange changeStart) {
    QRegularExpressionMatchIterator i = re.globalMatch(mText);
//    qWarning() << "text: " << mText;
    std::vector<Property> properties = {};
    while(i.hasNext()){
        auto word = i.next();
        auto text = word.captured(0);
        int start = word.capturedStart();
        auto propStart = Property(start, changeStart);
        properties.push_back(propStart);
    }
    return properties;
}

void DrawText::makePropertyList() {
//    auto bold = getProberties(QRegularExpression(" \\*\\*(.*?)\\*\\* "), fontChange::boldStart, fontChange::boldEnd);
    auto bold = getProberties(QRegularExpression("\\*\\*\\w(.*?)\\w\\*\\*"), fontChange::boldStart, fontChange::boldEnd);
//    auto bold = getProberties(QRegularExpression("\\*\\*\\w+\\*\\*"), fontChange::boldStart, fontChange::boldEnd);
    auto italic = getProberties(QRegularExpression("\\_\\w(.*?)\\w\\_"), fontChange::italicStart, fontChange::italicEnd);
    auto newLine = getProberties(QRegularExpression("\\n"), fontChange::newLine);
    auto itemize = getProberties(QRegularExpression("\\n\\s+\\* "), fontChange::itemize);
    mProp.insert(mProp.end(), italic.begin(), italic.end());
    mProp.insert(mProp.end(), bold.begin(), bold.end());
    mProp.insert(mProp.end(), newLine.begin(), newLine.end());
    mProp.insert(mProp.end(), itemize.begin(), itemize.end());
    std::sort(mProp.begin(), mProp.end(), [](auto a, auto b){return a.getPosition() < b.getPosition();});

    auto const firstProp = Property(0, fontChange::empty);
    auto const lastProp = Property(mText.size(), fontChange::empty);
    mProp.insert(mProp.begin(), firstProp);
    mProp.push_back(lastProp);

}

void DrawText::drawProperty(fontChange change, QString text, QPainter& painter) {
    auto font = painter.font();
    switch (change) {
        case fontChange::boldStart:
            font.setBold(true);
            painter.setFont(font);
            mFormateText.drawText(text.mid(2, text.size()-4), painter);
            break;
        case fontChange::boldEnd:
            font.setBold(false);
            painter.setFont(font);
            mFormateText.drawText(text, painter);
            break;
        case fontChange::italicStart:
            font.setItalic(true);
            painter.setFont(font);
            mFormateText.drawText(text.mid(1, text.size()-2), painter);
            break;
        case fontChange::italicEnd:
            font.setItalic(false);
            painter.setFont(font);
            mFormateText.drawText(text, painter);
            break;
        case fontChange::newLine:
            mFormateText.drawNewLine();
            mFormateText.drawText(text, painter);
            break;
        case fontChange::empty:
            mFormateText.drawText(text, painter);
            break;
        case fontChange::itemize:
            QRegularExpression re("\\* ");
            QRegularExpressionMatch match = re.match(text);
            auto const word = match.captured(0);
            auto const start = match.capturedStart();
            mFormateText.drawItem(painter);
            mFormateText.drawText(text.mid(start + 2), painter);
            break;
    }
}

void DrawText::drawWord(QPainter& painter) {
//    auto start = 0;
//    if(!mProp.empty()){
//        start = mProp.front().getPosition();
//    }
//    mFormateText.drawText(mText.left(start), painter);
    for(int i=0; i<int(mProp.size()); i++){
        drawProperty(mProp[i].getProperty(), mText.mid(mProp[i].getPosition(), mProp[i+1].getPosition()-mProp[i].getPosition()), painter);
    }

//    }
}
