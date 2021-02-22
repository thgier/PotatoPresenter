#include "box.h"
#include <QRegularExpression>

Box::Box(const BoxGeometry &rect, QString id)
    : mGeometry{rect}
    , mId{id}
{
}

void Box::setGeometry(const BoxGeometry &rect){
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
    rect.moveLeft(mStyle.mGeometry.left.value_or(geometry().rect().left()));
    rect.moveTop(mStyle.mGeometry.top.value_or(geometry().rect().top()));
    rect.setWidth(mStyle.mGeometry.width.value_or(geometry().rect().width()));
    rect.setHeight(mStyle.mGeometry.height.value_or(geometry().rect().height()));
    mGeometry.setAngle(mStyle.mGeometry.angle.value_or(geometry().angle()));
    auto font = painter.font();
    if(mStyle.mFontWeight == FontWeight::bold){
        font.setBold(true);
        painter.setFont(font);
    }
    font.setFamily(mStyle.mFont);
    font.setPixelSize(mStyle.mFontSize);
    painter.setFont(font);
    painter.setTransform(mGeometry.transform());
    painter.setOpacity(mStyle.mOpacity);
}

void Box::endDraw(QPainter &painter) const{
    painter.restore();
}

void Box::drawSelectionFrame(QPainter &painter){
    PainterTransformScope scope(this, painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto pen = painter.pen();
    auto const sizePen = 0.1;
    pen.setWidth(sizePen);
    painter.setPen(pen);
    painter.translate(QPoint(0, -sizePen));
    painter.drawRect(mGeometry.rect());
}

void Box::drawScaleHandle(QPainter &painter, int size){
    PainterTransformScope scope(this, painter);
    size /= 2;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    QPoint(size/2, size/2);
    painter.fillRect(QRect(mGeometry.rect().topLeft() + QPoint(-size/2, -size/2), QSize(size, size)), Qt::black);
    painter.fillRect(QRect(mGeometry.rect().topRight() + QPoint(size/2, -size/2), QSize(-size, size)), Qt::black);
    painter.fillRect(QRect(mGeometry.rect().bottomLeft() + QPoint(-size/2, size/2), QSize(size, -size)), Qt::black);
    painter.fillRect(QRect(mGeometry.rect().bottomRight() + QPoint(size/2, size/2), QSize(-size, -size)), Qt::black);
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

void Box::setPauseCounter(int counter) {
    mPauseCounter = counter;
}

bool Box::pauseCounterSmaller(int counter) const {
    return mPauseCounter <= counter;
}

int Box::pauseCounter() const {
    return mPauseCounter;
}
