#include "formatetext.h"
#include <QPainterPath>
#include <QDebug>
#include <QProcess>
#include <equationcachemanager.h>
#include <QCryptographicHash>


FormateText::FormateText(QFontMetrics metrics, QRect rect, QString id, double linespacing)
    : mMetrics{metrics}
    , mRect(rect)
    , mLineStart{metrics.xHeight()}
    , mLineY{double(rect.top() + metrics.ascent())}
    , mLinewidth{mLineStart}
    , mLinespacing{linespacing * metrics.lineSpacing()}
    , mIdBox{id}
{

}

void FormateText::drawText(QString text, QPainter& painter){
    if(mLatexNext) {
        drawTeX(text, painter);
        return;
    }
    mMetrics = painter.fontMetrics();
    QRegularExpression re("(\\S+)");
    QRegularExpressionMatchIterator i = re.globalMatch(text);
    QString word;
    while (i.hasNext()) {
        auto match = i.next();
        word = match.captured(1);
        if (mLinewidth + mMetrics.horizontalAdvance(word) > mRect.width() - mMetrics.xHeight()) {
            mLinewidth = mLineStart;
            mLineY += mLinespacing;
        }
        painter.drawText(mRect.left() + mLinewidth, mLineY, word);
        mLinewidth += mMetrics.horizontalAdvance(word);
        painter.drawText(mRect.left() + mLinewidth, mLineY, " ");
        mLinewidth += mMetrics.horizontalAdvance(" ");
    }
}

void FormateText::drawNewLine() {
    mLineStart = mMetrics.xHeight();
    mLinewidth = mLineStart;
    mLineY += mLinespacing;
}

void FormateText::drawNewHalfLine() {
    mLineStart = mMetrics.xHeight();
    mLinewidth = mLineStart;
    mLineY += 0.25 * mLinespacing;
}

void FormateText::drawItem(QPainter& painter) {
    auto const xHeight = painter.fontMetrics().xHeight();
    mLinewidth += 2 * xHeight;
    auto y = xHeight * 0.75;
    auto x = mLinewidth + xHeight / 2;
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(mRect.left() + x, mLineY - y, xHeight*0.55, xHeight*0.55);
    painter.setBrush(Qt::NoBrush);
    mLinewidth += 2 * xHeight;
    mLineStart = mLinewidth;
}

void FormateText::drawItemSecond(QPainter& painter) {
    auto const xHeight = painter.fontMetrics().xHeight();
    mLinewidth += 4 * xHeight;
    auto y = xHeight * 0.77;
    auto x = mLinewidth + xHeight / 2;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(mRect.left() + x, mLineY - y, xHeight*0.55, xHeight*0.55);
    painter.setBrush(Qt::NoBrush);
    mLinewidth += 2 * xHeight;
    mLineStart = mLinewidth;
}

void FormateText::drawTeX(QString mathExpression, QPainter &painter){
    auto const hash = QCryptographicHash::hash(mathExpression.toUtf8(), QCryptographicHash::Sha1).toHex().left(8);
    auto const equation = cacheManager().getCachedImage(hash);
    switch(equation.status){
    case SvgStatus::error:
        painter.save();
        painter.setPen(Qt::red);
        drawText("LaTeX error", painter);
        painter.restore();
        break;
    case SvgStatus::notStarted:
        cacheManager().startConversionProcess(mathExpression, hash);
        break;
    case SvgStatus::pending:
        break;
    case SvgStatus::success:
        drawSvg(equation.svg, painter);
        break;
    }
}

void FormateText::drawSvg(std::shared_ptr<QSvgRenderer> image, QPainter& painter){
    if(!image){
        return;
    }
    if(!image->isValid()){
        return;
    }
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
    auto const point = QPointF{1.0 * mRect.left() + mLinewidth, mLineY - height + descent};
    auto const paintRect = QRectF(point, QSize(width, height));
    image->render(&painter, paintRect);
    mLinewidth += width;
}

void FormateText::setLatexNext(bool latexNext) {
    mLatexNext = latexNext;
}

