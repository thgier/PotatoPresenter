#include "formatetext.h"
#include <QPainterPath>
#include <QDebug>
#include <QProcess>
#include <QSvgRenderer>
#include <equationcachemanager.h>
#include <QCryptographicHash>


FormateText::FormateText(QFontMetrics metrics, QRect rect, QString id)
    : mMetrics{metrics}
    , mRect(rect)
    , mLineStart{metrics.xHeight()}
    , mLinewidth{mLineStart}
    , mLinePositions{getLinePosition()}
    , mIdBox{id}
{

}

std::vector<int> FormateText::getLinePosition() const{
    auto const fontSize = mMetrics.height();
    auto const lineSpacing = mMetrics.lineSpacing();
    auto const numberOfLines = mRect.height() / lineSpacing;
    auto const offset = .5 * (mRect.height() - (numberOfLines - 1) * lineSpacing - fontSize);
    auto const ascent = mMetrics.ascent();
    std::vector<int> linePosition = {};
    for(int i=0; i<numberOfLines + 2; i++) {
        linePosition.push_back(mRect.top() + ascent + offset + i * lineSpacing);
    }
    return linePosition;
}

void FormateText::drawText(QString text, QPainter& painter){
    mMetrics = painter.fontMetrics();
    QRegularExpression re("(\\S+)");
    QRegularExpressionMatchIterator i = re.globalMatch(text);
    QString word;
    while (i.hasNext()) {
        auto match = i.next();
        word = match.captured(1);
        if (mLinewidth + mMetrics.horizontalAdvance(word) > mRect.width() - mMetrics.xHeight()) {
            mLineN++;
            mLinewidth = mLineStart;
        }
        if (mLineN < int(mLinePositions.size())) {
            painter.drawText(mRect.left() + mLinewidth, mLinePositions[mLineN], word);
            mLinewidth += mMetrics.horizontalAdvance(word);
            painter.drawText(mRect.left() + mLinewidth, mLinePositions[mLineN], " ");
            mLinewidth += mMetrics.horizontalAdvance(" ");
        }
    }
}

void FormateText::drawNewLine() {
    mLineStart = mMetrics.xHeight();
    mLineN++;
    mLinewidth = mLineStart;
}

void FormateText::drawItem(QPainter& painter) {
    auto const xHeight = painter.fontMetrics().xHeight();
    auto y = xHeight * 0.7;
    auto x = mLinewidth + xHeight / 2;
    painter.setBrush(Qt::black);
    painter.drawEllipse(mRect.left()+x, mLinePositions[mLineN] - y, xHeight*0.45, xHeight*0.45);
    painter.setBrush(Qt::NoBrush);
    mLinewidth += 1.5 * xHeight;
    mLineStart = mLinewidth;
}

void FormateText::drawTeX(QString mathExpression, QPainter &painter){
    auto const hash = QCryptographicHash::hash(mathExpression.toUtf8(), QCryptographicHash::Sha1).toHex().left(8);
    auto const image = cacheManager().getCachedImage(hash);
    if(!image){
        cacheManager().startConversionProcess(mathExpression, hash);
        return;
    }
    if(!image->isValid()){return;}
    if(image->defaultSize().width() == 0){
        return;
    }
    qWarning() << "view box" << image->viewBox();
    auto const fontSize = painter.font().pixelSize();
    auto const descent = painter.fontMetrics().descent();
    auto const defaultSize = image->defaultSize();
    qWarning() << defaultSize;
    auto const height = 1.0 * defaultSize.height() / 8.5 * fontSize;
    auto const width = 1.0 * defaultSize.width() / defaultSize.height() * height;
    image->setAspectRatioMode(Qt::KeepAspectRatio);
    auto const point = QPoint{mRect.left() + mLinewidth, mLinePositions[mLineN] - int(height) + descent};
    auto const paintRect = QRectF(point, QSize(width, height));
    image->render(&painter, paintRect);
    mLinewidth += width;
}

