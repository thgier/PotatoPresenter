#include "paintdocument.h"

#include<QPainter>
#include "painter.h"

PaintDocument::PaintDocument()
    : QWidget(), mWidth{frameSize().width()}, pageNumber{0}
    , mLayout{Layout(aspectRatio::sixteenToNine)}
{
    setMouseTracking(true);
    mSize = mLayout.mSize;
    mScale = 1.0 * mSize.width() / mWidth;
}

void PaintDocument::paintEvent(QPaintEvent*)
{
    painter.begin(this);
    painter.setViewport(QRect(0, 0, mWidth, 1.0 * mWidth/mSize.width()*mSize.height()));
    painter.setWindow(QRect(QPoint(0, 0), mSize));
    auto font = QFont(mFont);
    font.setPixelSize(mFontSize);
    painter.setFont(font);
//    painter.scale(mScale, mScale);
    painter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);
    if(mBoxInFocus != nullptr){
        drawBoundingBox(mBoxInFocus->Rect());
    }
    if(!mFrames.empty()){
        auto paint = std::make_shared<Painter>(painter);
        paint->paintFrame(mFrames[pageNumber]);
    }
    painter.end();
}

void PaintDocument::setFrames(std::vector<std::shared_ptr<Frame>> frames) {
    if( pageNumber >= int(frames.size())){
        pageNumber = int(frames.size()) - 1;
    }
    if(pageNumber == -1) {
        pageNumber = 0;
    }
    mFrames = frames;
}

void PaintDocument::setCurrentPage(int page){
    if(page >= int(mFrames.size()) || page < 0) {
        return;
    }
    pageNumber = page;
    update();
}

void PaintDocument::resizeEvent(QResizeEvent*) {
    mWidth = frameSize().width();
    mScale = 1.0 * mSize.width() / mWidth;
}

void PaintDocument::determineBoxInFocus(QPoint mousePos){
    mBoxInFocus = nullptr;
    for(auto box: mFrames[pageNumber]->getBoxes()) {
        auto const boxMargins = box->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(boxMargins.contains(mousePos)) {
            mBoxInFocus = box;
            break;
        }
    }
}

void PaintDocument::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    lastPosition = event->pos() * mScale;
    if(mBoxInFocus){
        auto boxMargins = mBoxInFocus->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(!boxMargins.contains(lastPosition)){
            determineBoxInFocus(lastPosition);
        }
    }
    else{
        determineBoxInFocus(lastPosition);
    }
    if(!mBoxInFocus) {
        return;
    }
    auto const trafoType = getTransformationType(lastPosition);
    qWarning() << "trafotype" << trafoType;
    momentTrafo = BoxTransformation(*mBoxInFocus.get(), trafoType);
    CursorApperance(lastPosition);
}

void PaintDocument::mouseDoubleClickEvent(QMouseEvent *event){
    auto const mousePos = event->pos() * mScale;
    if(!mBoxInFocus){
        determineBoxInFocus(mousePos);
        return;
    }
    for(auto box: mFrames[pageNumber]->getBoxes()) {
        auto const boxMargins = box->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(boxMargins.contains(mousePos) && mBoxInFocus != box) {
            mBoxInFocus = box;
            break;
        }
    }
}

void PaintDocument::mouseMoveEvent(QMouseEvent *event)
{
    CursorApperance(event->pos() * mScale);
    if ((event->buttons() & Qt::LeftButton)) {
        auto const newPosition = event->pos() * mScale;
        momentTrafo->makeTransformation(newPosition - lastPosition);
        lastPosition = newPosition;
        update();
    }
}

void PaintDocument::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
//        TODO: maybe translate again
        momentTrafo.reset();
        update();
    }
}

TransformationType PaintDocument::getTransformationType(QPoint mousePosition){
    if(!mBoxInFocus){
        return {};
    }
    auto cursor = QCursor();
    auto const rect = mBoxInFocus->Rect();
    TransformationType type = {};
    if((rect.topLeft() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationType::scaleTopLeft;
        cursor.setShape(Qt::SizeFDiagCursor);
    }
    else if((rect.topRight() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationType::scaleTopRight;
        cursor.setShape(Qt::SizeBDiagCursor);
    }
    else if((rect.bottomLeft() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationType::scaleBottomLeft;
        cursor.setShape(Qt::SizeBDiagCursor);
    }
    else if((rect.bottomRight() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationType::scaleBottomRight;
        cursor.setShape(Qt::SizeFDiagCursor);
    }
    else if(abs(rect.top() - mousePosition.y()) < diffToMouse){
        type = TransformationType::scaleTop;
        cursor.setShape(Qt::SizeVerCursor);
    }
    else if(abs(rect.bottom() - mousePosition.y()) < diffToMouse){
        type = TransformationType::scaleBottom;
        cursor.setShape(Qt::SizeVerCursor);
    }
    else if(abs(rect.left() - mousePosition.x()) < diffToMouse){
        type = TransformationType::scaleLeft;
        cursor.setShape(Qt::SizeHorCursor);
    }
    else if(abs(rect.right() - mousePosition.x()) < diffToMouse){
        type = TransformationType::scaleRight;
        cursor.setShape(Qt::SizeHorCursor);
    }
    else if(rect.contains(mousePosition)){
        type = TransformationType::translate;
        cursor.setShape(Qt::ArrowCursor);
    }
    setCursor(cursor);
    return type;
}

void PaintDocument::CursorApperance(QPoint mousePosition){
    auto cursor = QCursor();
    if(mBoxInFocus == nullptr){
        return;
    }
    auto const rect = mBoxInFocus->Rect();
    if((rect.topLeft() - mousePosition).manhattanLength() < diffToMouse || (rect.bottomRight() - mousePosition).manhattanLength() < diffToMouse){
        cursor.setShape(Qt::SizeFDiagCursor);
    }
    else if((rect.topRight() - mousePosition).manhattanLength() < diffToMouse || (rect.bottomLeft() - mousePosition).manhattanLength() < diffToMouse) {
        cursor.setShape(Qt::SizeBDiagCursor);
    }
    else if(abs(rect.top() - mousePosition.y()) < diffToMouse || abs(rect.bottom() - mousePosition.y()) < diffToMouse) {
        cursor.setShape(Qt::SizeVerCursor);
    }
    else if(abs(rect.left() - mousePosition.x()) < diffToMouse || abs(rect.right() - mousePosition.x()) < diffToMouse) {
        cursor.setShape(Qt::SizeHorCursor);
    }
    else if(rect.contains(mousePosition)){
        cursor.setShape(Qt::SizeAllCursor);
    }
    else{
        cursor.setShape(Qt::ArrowCursor);
    }
    setCursor(cursor);
}

void PaintDocument::createPDF(){
    QPdfWriter pdfWriter("/home/theresa/Documents/praes/file.pdf");
    auto const pdfLayout = QPageLayout(QPageSize(QSize(160, 90)), QPageLayout::Portrait, QMarginsF(0, 0, 0, 0), QPageLayout::Millimeter);
    pdfWriter.setPageLayout(pdfLayout);

    QPainter painter(&pdfWriter);
    painter.setWindow(QRect(QPoint(0, 0), mSize));

    auto font = QFont(mFont);
    font.setPixelSize(mFontSize);
    painter.setFont(font);

    painter.begin(&pdfWriter);
    for(auto frame: mFrames){
        auto paint = std::make_shared<Painter>(painter);
        paint->paintFrame(frame);
        if(frame != mFrames.back()){
            pdfWriter.newPage();
        }
    }
    painter.end();
}

std::shared_ptr<Box> PaintDocument::activeBox(){
    return mBoxInFocus;
}

void PaintDocument::layoutTitle(){
    if(!mBoxInFocus) {
        return;
    }
    mBoxInFocus->setRect(mLayout.mTitlePos);
    update();
}

void PaintDocument::layoutBody(){
    if(!mBoxInFocus) {
        return;
    }
    mBoxInFocus->setRect(mLayout.mBodyPos);
    update();
}

void PaintDocument::layoutFull(){
    if(!mBoxInFocus) {
        return;
    }
    mBoxInFocus->setRect(mLayout.mFullPos);
    update();
}

void PaintDocument::layoutLeft(){
    if(!mBoxInFocus) {
        return;
    }
    mBoxInFocus->setRect(mLayout.mLeftPos);
    update();
}

void PaintDocument::layoutRight(){
    if(!mBoxInFocus) {
        return;
    }
    mBoxInFocus->setRect(mLayout.mRightPos);
    update();
}

void PaintDocument::drawBoundingBox(QRect rect) {
    painter.save();
    auto pen = painter.pen();
    auto const sizePen = 0.1;
    pen.setWidth(sizePen);
    painter.setPen(pen);
    auto brush = painter.brush();
    brush.setStyle(Qt::NoBrush);
    painter.setBrush(brush);
    painter.translate(QPoint(0, -sizePen));
    painter.drawRect(rect);
    drawScaleMarker(rect);
    painter.restore();
}

void PaintDocument::drawScaleMarker(QRect rect){
    painter.setBrush(Qt::black);
    auto const w = diffToMouse;
    painter.fillRect(QRect(rect.topLeft(), QSize(w, w)), Qt::black);
    painter.fillRect(QRect(rect.topRight(), QSize(-w, w)), Qt::black);
    painter.fillRect(QRect(rect.bottomLeft(), QSize(w, -w)), Qt::black);
    painter.fillRect(QRect(rect.bottomRight(), QSize(-w, -w)), Qt::black);

    painter.setBrush(Qt::NoBrush);
}

