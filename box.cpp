#include "box.h"
#include <QRegularExpression>

Box::Box(BoxGeometry rect, QString id)
    : mGeometry{rect}
    , mId{id}
{
}

void Box::setGeometry(BoxGeometry rect){
    if(mMovable){
        mGeometry = rect;
    }
}

BoxGeometry Box::geometry() const{
    return mGeometry;
}

BoxStyle Box::style() const{
    return mStyle;
}

void Box::drawContent(QPainter& painter, std::map<QString, QString>) {
    startDraw(painter);
    auto pen = painter.pen();
    auto const sizeBrush = 0.1;
    pen.setWidth(sizeBrush);
    painter.setPen(pen);
    painter.translate(QPoint(0, -sizeBrush));
    painter.drawRect(mGeometry.rect());
    painter.rotate(-mGeometry.angle());
    endDraw(painter);
}


void Box::setVisibility(bool vis){
    mVisible = vis;
}

void Box::setMovable(bool move) {
    mMovable = move;
}

QString Box::id() {
    return mId;
}

void Box::startDraw(QPainter &painter){
    painter.save();
    auto rect = mGeometry.rect();
    if(mStyle.left != -1){
        rect.moveLeft(mStyle.left);
    }
    if(mStyle.top != -1){
        rect.moveTop(mStyle.top);
    }
    if(mStyle.width != -1){
        rect.setWidth(mStyle.width);
    }
    if(mStyle.height != -1){
        rect.setHeight(mStyle.height);
    }
    mGeometry.setRect(rect);
    if(mStyle.angle != -1){
        mGeometry.setAngle(mStyle.angle);
    }
    painter.setTransform(mGeometry.transform());
    painter.setOpacity(mStyle.mOpacity);
}

void Box::endDraw(QPainter &painter) const{
    painter.restore();
}

void Box::drawBoundingBox(QPainter &painter){
    startDraw(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto pen = painter.pen();
    auto const sizePen = 0.1;
    pen.setWidth(sizePen);
    painter.setPen(pen);
    painter.translate(QPoint(0, -sizePen));
    painter.drawRect(mGeometry.rect());
    endDraw(painter);
}

void Box::drawScaleMarker(QPainter &painter, int size){
    size /= 2;
    startDraw(painter);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    QPoint(size/2, size/2);
    painter.fillRect(QRect(mGeometry.rect().topLeft() + QPoint(-size/2, -size/2), QSize(size, size)), Qt::black);
    painter.fillRect(QRect(mGeometry.rect().topRight() + QPoint(size/2, -size/2), QSize(-size, size)), Qt::black);
    painter.fillRect(QRect(mGeometry.rect().bottomLeft() + QPoint(-size/2, size/2), QSize(size, -size)), Qt::black);
    painter.fillRect(QRect(mGeometry.rect().bottomRight() + QPoint(size/2, size/2), QSize(-size, -size)), Qt::black);

    endDraw(painter);
}

void Box::setBoxStyle(BoxStyle style){
    mStyle = style;
}

QString Box::substituteVariables(QString text, std::map<QString, QString> variables) const {
    if(variables.empty()){
        return text;
    }
    std::vector<VariableSubstitution> variableSubstituions;
    for(auto const &variable: variables){
        QRegularExpression re(variable.first);
        QRegularExpressionMatchIterator i = re.globalMatch(text);
        while(i.hasNext()){
            QRegularExpressionMatch match = i.next();
            VariableSubstitution sub;
            sub.begin = match.capturedStart();
            sub.end = match.capturedEnd();
            sub.word = variable.second;
            variableSubstituions.push_back(sub);
        }
    }
    if(variableSubstituions.empty()){
        return text;
    }
    std::sort(variableSubstituions.begin(), variableSubstituions.end(), [](auto a, auto b){return a.begin < b.begin;});
    QString newText = "";
    int position = 0;
    for(auto &sub: variableSubstituions){
        newText.append(text.midRef(position, sub.begin - position));
        newText.append(sub.word);
        position = sub.end;
    }
    newText.append(text.midRef(position, text.size() - position));
    return newText;
}

