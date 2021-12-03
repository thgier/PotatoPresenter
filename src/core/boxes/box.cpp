/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "box.h"
#include <QRegularExpression>

namespace{
Qt::PenStyle CSSToPenStyle(QString cssStyle) {
    if (cssStyle == "dotted") {
        return Qt::PenStyle::DotLine;
    }
    else if(cssStyle == "dashed") {
        return Qt::PenStyle::DashLine;
    }
    return Qt::PenStyle::SolidLine;
}
}


BoxStyle const& Box::style() const{
    return mStyle;
}

BoxStyle& Box::style() {
    return mStyle;
}

const BoxGeometry &Box::geometry() const {
    return mStyle.mGeometry;
}

BoxGeometry &Box::geometry()  {
    return mStyle.mGeometry;
}

const QString Box::id() const {
    return style().id();
}

void Box::setId(QString const& id) {
    mStyle.mId = id;
}

QString Box::configId() const {
    return style().configId();
}

void Box::setConfigId(QString configId) {
    mStyle.mConfigId = configId;
}

int Box::line() const {
    return style().line();
}

void Box::startDraw(QPainter &painter) {
    painter.save();

    // geometry
    auto rect = style().mGeometry.rect();
    rect.moveLeft(mStyle.mGeometry.left());
    rect.moveTop(mStyle.mGeometry.top());
    rect.setWidth(mStyle.mGeometry.width());
    rect.setHeight(mStyle.mGeometry.height());
    style().mGeometry.setAngle(mStyle.mGeometry.angle());

    painter.setTransform(style().mGeometry.transform());
    painter.setRenderHint(QPainter::Antialiasing);

    // font
    auto font = painter.font();
    if(mStyle.mFontWeight == FontWeight::bold){
        font.setBold(true);
        painter.setFont(font);
    }
    font.setFamily(mStyle.font());
    // font size is in pt, factor to get pixel 1.9
    font.setPixelSize(mStyle.fontSize() * 1.9);
    painter.setFont(font);
    painter.setPen(style().color());
    painter.setOpacity(mStyle.opacity());
}

void Box::endDraw(QPainter &painter) const{
    painter.restore();
}

void Box::drawManipulationSlide(QPainter &painter, int size){
    PainterTransformScope scope(this, painter);
    auto pen = painter.pen();
    pen.setColor(Qt::black);
    pen.setCosmetic(true);
    painter.setPen(pen);

    auto const rect = geometry().rect();
    painter.drawRect(rect);

    painter.fillRect(QRect(rect.topLeft() + QPoint(-size/2, -size/2), QSize(size, size)), Qt::white);
    painter.fillRect(QRect(rect.topRight() + QPoint(size/2, -size/2), QSize(-size, size)), Qt::white);
    painter.fillRect(QRect(rect.bottomLeft() + QPoint(-size/2, size/2), QSize(size, -size)), Qt::white);
    painter.fillRect(QRect(rect.bottomRight() + QPoint(size/2, size/2), QSize(-size, -size)), Qt::white);

    painter.drawRect(QRect(rect.topLeft() + QPoint(-size/2, -size/2), QSize(size, size)));
    painter.drawRect(QRect(rect.topRight() + QPoint(size/2, -size/2), QSize(-size, size)));
    painter.drawRect(QRect(rect.bottomLeft() + QPoint(-size/2, size/2), QSize(size, -size)));
    painter.drawRect(QRect(rect.bottomRight() + QPoint(size/2, size/2), QSize(-size, -size)));
}

void Box::drawGlobalBoxSettings(QPainter &painter) {
    PainterTransformScope scope(this, painter);

    auto const rect = geometry().rect();

    // background Color
    if(style().mBackgroundColor) {
        painter.save();
        painter.setBrush(mStyle.backgroundColor());
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(geometry().rect(), style().borderRadius(), style().borderRadius());
        painter.restore();
    }

    // border
    if(mStyle.hasBorder()) {
        painter.save();
        auto pen = painter.pen();
        pen.setColor(mStyle.borderColor());
        pen.setWidth(mStyle.borderWidth());
        if(mStyle.borderStyle() == "double") {
            painter.setPen(pen);
            painter.drawRoundedRect(rect, style().borderRadius(), style().borderRadius());
            auto const borderWidth = 2 * mStyle.borderWidth();
            auto const margins = QMargins(borderWidth, borderWidth, borderWidth, borderWidth);
            painter.drawRoundedRect(rect.marginsAdded(margins), style().borderRadius(), style().borderRadius());
        }
        else {
            pen.setStyle(CSSToPenStyle(mStyle.borderStyle()));
            painter.setPen(pen);
            painter.drawRoundedRect(rect, style().borderRadius(), style().borderRadius());
        }
        painter.restore();
    }
}

bool Box::containsPoint(QPoint point, int margin) const {
    return geometry().contains(point, margin);
}

void Box::setBoxStyle(BoxStyle style){
    mStyle = style;
}

QString Box::substituteVariables(QString text, std::map<QString, QString> variables) const {
    if(variables.empty()){
        return text;
    }
    static QRegularExpression re("%{[^}]*}");
    QRegularExpressionMatchIterator i = re.globalMatch(text);
    QString newText = "";
    int position = 0;
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();
        auto const begin = match.capturedStart();
        auto const end = match.capturedEnd();
        newText.append(text.midRef(position, begin - position));
        auto const foundExpression = text.mid(begin, end - begin);
        if( variables.find(foundExpression) != variables.end() ) {
            auto const value = variables.find(foundExpression)->second;
            newText.append(value);
            position = end;
        }
    }
    newText.append(text.midRef(position, text.size() - position));
    return newText;
}

void Box::setPauseCounter(int counter) {
    mPauseCounter = counter;
}

void Box::setGeometry(const BoxGeometry &geometry) {
    mStyle.mGeometry = geometry;
}

void Box::setGeometry(const MemberBoxGeometry &geometry) {
    mStyle.mGeometry = BoxGeometry(geometry);
}

void Box::setPauseMode(PauseDisplayMode mode) {
    mPauseMode = mode;
}

std::pair<int, PauseDisplayMode> Box::pauseCounter() const {
    return std::pair(mPauseCounter, mPauseMode);
}
