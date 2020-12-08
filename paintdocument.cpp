#include "paintdocument.h"

#include<QPainter>
#include "painter.h"

PaintDocument::PaintDocument(QWidget*&)
    : QWidget(), mWidth{frameSize().width()}, pageNumber{0}
    , mLayout{Layout(aspectRatio::sixteenToNine)}
{
    setMouseTracking(true);
    mSize = mLayout.mSize;
    mScale = 1.0 * mSize.width() / mWidth;
}

void PaintDocument::setPresentation(Presentation* pres){
    mPresentation = pres;
}

void PaintDocument::paintEvent(QPaintEvent*)
{
    painter.begin(this);
    painter.setViewport(QRect(0, 0, mWidth, 1.0 * mWidth/mSize.width()*mSize.height()));
    painter.setWindow(QRect(QPoint(0, 0), mSize));
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
//    painter.scale(mScale, mScale);
    painter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);
    if(!mPresentation->empty()){
        auto paint = std::make_shared<Painter>(painter);
        paint->paintFrame(mPresentation->at(pageNumber));
    }
    if(mPresentation->getBox(mActiveBoxId) != nullptr){
        drawBoundingBox(mPresentation->getBox(mActiveBoxId)->Rect());
    }
    auto font = painter.font();
    font.setPixelSize(50);
    painter.setFont(font);
    painter.drawText(QRect(0, mSize.height(), mSize.width(), 80), Qt::AlignCenter, mCurrentFrameId);
    painter.end();
}

QSize PaintDocument::sizeHint() const{
    return mLayout.mSize;
}

void PaintDocument::updateFrames(){
    setCurrentPage(mCurrentFrameId);
    update();
}

void PaintDocument::setCurrentPage(int page){
    if(page >= int(mPresentation->size()) || page < 0) {
        return;
    }
    pageNumber = page;
    mCurrentFrameId = mPresentation->at(page)->id();
    mActiveBoxId = QString();
    selectionChanged(mPresentation->at(pageNumber));
    update();
}

void PaintDocument::setCurrentPage(QString id){
    int counter = 0;
    for(auto const & frame: mPresentation->frames()) {
        if(frame->id() == id) {
            if(pageNumber != counter){
                mActiveBoxId = QString();
            }
            pageNumber = counter;
            emit pageNumberChanged(pageNumber);
            break;
        }
        counter++;
    }
}

void PaintDocument::resizeEvent(QResizeEvent*) {
    mWidth = frameSize().width();
    mScale = 1.0 * mSize.width() / mWidth;
}

void PaintDocument::determineBoxInFocus(QPoint mousePos){
    mActiveBoxId = QString();
    for(auto box: mPresentation->at(pageNumber)->getBoxes()) {
        auto const boxMargins = box->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(boxMargins.contains(mousePos)) {
            mActiveBoxId = box->id();
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
    if(!mActiveBoxId.isEmpty()){
        auto const boxMargins = mPresentation->getBox(mActiveBoxId)->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(!boxMargins.contains(lastPosition)){
            determineBoxInFocus(lastPosition);
        }
    }
    else{
        determineBoxInFocus(lastPosition);
    }
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    auto const trafoType = getTransformationType(lastPosition);
    qWarning() << "trafotype" << trafoType;
    momentTrafo = BoxTransformation(mPresentation->getBox(mActiveBoxId), trafoType, pageNumber);
    CursorApperance(lastPosition);
}

void PaintDocument::mouseDoubleClickEvent(QMouseEvent *event){
    auto const mousePos = event->pos() * mScale;
    if(mActiveBoxId.isEmpty()){
        determineBoxInFocus(mousePos);
        return;
    }
    for(auto box: mPresentation->at(pageNumber)->getBoxes()) {
        auto const boxMargins = box->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(boxMargins.contains(mousePos) && mActiveBoxId != box->id()) {
            mActiveBoxId = box->id();
            break;
        }
    }
}

void PaintDocument::mouseMoveEvent(QMouseEvent *event)
{
    CursorApperance(event->pos() * mScale);
    if ((event->buttons() & Qt::LeftButton)) {
        auto const newPosition = event->pos() * mScale;
        momentTrafo->makeTransformation(newPosition - lastPosition, mPresentation);
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
    if(mActiveBoxId.isEmpty()){
        return {};
    }
    auto cursor = QCursor();
    auto const rect = mPresentation->getBox(mActiveBoxId)->Rect();
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
    if(mActiveBoxId.isEmpty()){
        return;
    }
    auto const rect = mPresentation->getBox(mActiveBoxId)->Rect();
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

    painter.begin(&pdfWriter);
    for(auto frame: mPresentation->frames()){
        auto paint = std::make_shared<Painter>(painter);
        paint->paintFrame(frame);
        if(frame != mPresentation->frames().back()){
            pdfWriter.newPage();
        }
    }
    painter.end();
}

void PaintDocument::layoutTitle(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mTitlePos, pageNumber);
    update();
}

void PaintDocument::layoutBody(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mBodyPos, pageNumber);
    update();
}

void PaintDocument::layoutFull(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mFullPos, pageNumber);
    update();
}

void PaintDocument::layoutLeft(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mLeftPos, pageNumber);
    update();
}

void PaintDocument::layoutRight(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mRightPos, pageNumber);
    update();
}

void PaintDocument::layoutPresTitle(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mPresTitlePos, pageNumber);
    update();
}

void PaintDocument::layoutSubtitle(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBox(mActiveBoxId, mLayout.mSubtitlePos, pageNumber);
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

