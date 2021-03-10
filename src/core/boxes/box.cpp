#include "box.h"
#include <QRegularExpression>

Box::Box(const BoxStyle &boxStyle, const QString &id, int line)
    : mStyle{boxStyle}
    , mId{id}
    , mLine{line}
{
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

const QString &Box::id() const {
    return mId;
}

void Box::setId(QString const& id) {
    mId = id;
}

QString Box::configId() const {
    return mConfigId.value_or(mId);
}

void Box::setConfigId(QString configId) {
    mConfigId = configId;
}

int Box::line() const {
    return mLine;
}

void Box::startDraw(QPainter &painter) {
    painter.save();
    auto rect = style().mGeometry.rect();
    rect.moveLeft(mStyle.mGeometry.left());
    rect.moveTop(mStyle.mGeometry.top());
    rect.setWidth(mStyle.mGeometry.width());
    rect.setHeight(mStyle.mGeometry.height());
    style().mGeometry.setAngle(mStyle.mGeometry.angle());
    auto font = painter.font();
    if(mStyle.mFontWeight == FontWeight::bold){
        font.setBold(true);
        painter.setFont(font);
    }
    font.setFamily(mStyle.font());
    font.setPixelSize(mStyle.fontSize());
    painter.setFont(font);
    painter.setTransform(style().mGeometry.transform());
    painter.setOpacity(mStyle.opacity());
}

void Box::endDraw(QPainter &painter) const{
    painter.restore();
}

void Box::drawSelectionFrame(QPainter &painter){
    PainterTransformScope scope(this, painter);
    painter.setRenderHint(QPainter::Antialiasing);
    auto pen = painter.pen();
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.drawRect(style().mGeometry.rect());
}

void Box::drawScaleHandle(QPainter &painter, int size){
    PainterTransformScope scope(this, painter);
    size /= 2;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    QPoint(size/2, size/2);
    painter.fillRect(QRect(style().mGeometry.rect().topLeft() + QPoint(-size/2, -size/2), QSize(size, size)), Qt::black);
    painter.fillRect(QRect(style().mGeometry.rect().topRight() + QPoint(size/2, -size/2), QSize(-size, size)), Qt::black);
    painter.fillRect(QRect(style().mGeometry.rect().bottomLeft() + QPoint(-size/2, size/2), QSize(size, -size)), Qt::black);
    painter.fillRect(QRect(style().mGeometry.rect().bottomRight() + QPoint(size/2, size/2), QSize(-size, -size)), Qt::black);
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
