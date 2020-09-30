#include "textfield.h"

#include <QDebug>
#include<QGraphicsTextItem>
#include<QRegularExpression>
#include <vector>
#include<QMargins>

TextField::TextField(QString text, QRect rect)
    : Box(rect), mText(text), mCharNumber{0}
{
}

QString TextField::Text(){
    return mText;
}

void TextField::drawContent(QPainter& painter) {
//    auto pen = painter.pen();
//    auto const sizeBrush = 0.1;
//    pen.setWidth(sizeBrush);
//    painter.setPen(pen);
//    painter.translate(QPoint(0, -sizeBrush));
//    painter.drawRect(Box::Rect());
    auto draw = DrawText(mText, painter, Box::Rect());
    draw.drawWord(painter);
}

//int TextField::drawText(int x, int y, QString text, QPainter& painter) {
//    auto bold = getProberties(QRegularExpression(" \\*\\*\\w(.*?)\\w\\*\\* "), fontChange::bold);
//    auto italic = getProberties(QRegularExpression(" \\_\\w(.*?)\\w\\_ "), fontChange::italic);
//    QRegularExpression boldStart("(\\*\\*\\w+)");
//    QRegularExpressionMatch matchStart = boldStart.match(text);
//    QRegularExpression boldEnd("(\\w+\\*\\*)");
//    QRegularExpressionMatch matchEnd = boldEnd.match(text);
//    if(matchStart.hasMatch()) {
//        auto font = painter.font();
//        font.setBold(true);
//        painter.setFont(font);
//        text = text.right(text.length()-2);
//    }
//    if (matchEnd.hasMatch()){
//        text = text.chopped(3);
//        text.append(" ");
//    }

//    painter.drawText(x, y, text);
//    int width = painter.fontMetrics().horizontalAdvance(text);

//    if(matchEnd.hasMatch()) {
//        auto font = painter.font();
//        font.setBold(false);
//        painter.setFont(font);
//    }
//    return width;
//}

void TextField::renderText(QPainter& painter){
//    auto draw = DrawText(mText, painter, Box::Rect());
//    draw.drawWord(painter);
//    get layout stuff
//    auto fontMetrics = painter.fontMetrics();
//    auto fontSize = fontMetrics.height();
//    auto lineSpacing = fontMetrics.lineSpacing();
//    auto numberLines = Box::Rect().height() / lineSpacing;
//    auto offset = .5 * (Box::Rect().height() - (numberLines - 1) * lineSpacing - fontSize);
//    auto ascent = fontMetrics.ascent();
//    std::vector<int> linePosition = {};
//    for(int i=0; i<numberLines + 2; i++) {
//        linePosition.push_back(Box::Rect().top() + ascent + offset + i * lineSpacing);
//    }
//    auto left = Box::Rect().left();

//    translate markdown
//    QRegularExpression re("(\\S+)");
//    QRegularExpressionMatchIterator i = re.globalMatch(mText);
//    int lineNumber = 0;
//    QString word;
//    auto linewidth = fontMetrics.xHeight();
//    while (i.hasNext()) {
//        auto match = i.next();
//        word = match.captured(1);
//        if (linewidth + fontMetrics.horizontalAdvance(word) > Box::Rect().width() - fontMetrics.xHeight()) {
//            lineNumber++;
//            linewidth = fontMetrics.xHeight();
//        }
//        if (lineNumber < numberLines + 2) {
//            linewidth += draw.drawWord(left + linewidth, linePosition[lineNumber], word, painter);
//            linewidth += draw.drawWord(left + linewidth, linePosition[lineNumber], " ", painter);
//        }
//    }

//    QRegularExpression re("(\\*\\*\\w+\\*\\*)");
//    QRegularExpressionMatchIterator i = re.globalMatch(text);
//    QStringList words;
//    while (i.hasNext()) {
//        QRegularExpressionMatch match = i.next();
//        auto start = match.capturedStart();
//       QRect boundingRect;
//        auto lineHeight = painter.fontMetrics().height();
//        painter.drawText(Box::Rect().left(), Box::Rect().top() + lineHeight, text.mid(0, start));
//        QString word = match.captured(1);
//        qWarning() << word.mid(2, word.size()-4);
//        painter.save();
//        QRegularExpression bold("(\\*\\*\\w+\\*\\*)");
//        if(bold.match(word).hasMatch()){
//            auto font = painter.font();
//            font.setBold(true);
//            painter.setFont(font);
//            auto fontMetrics = painter.fontMetrics();
//            auto textWidth = fontMetrics.horizontalAdvance(text.mid(0, start));
//            painter.drawText(Box::Rect().left() + textWidth, Box::Rect().top() + lineHeight, word.mid(2, word.size()-4));
//        }
//        painter.restore();
//    }
//    qWarning() << words;
//    painter.restore();
}

//std::vector<Proberty> TextField::getProberties(QRegularExpression re, fontChange change) {
//    QRegularExpression re(" \\*\\*\\w(.*?)\\w\\*\\* ");
//    QRegularExpressionMatchIterator i = re.globalMatch(mText);
//    std::vector<Proberty> properties = {};
//    while(i.hasNext()){
//        auto word = i.next();
//        int start = word.capturedStart();
//        int end = word.capturedEnd();
//        auto prob = Proberty(start, end, change);
//        properties.push_back(prob);
//    }
//    return properties;
//}
