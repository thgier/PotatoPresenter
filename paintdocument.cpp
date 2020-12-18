#include "paintdocument.h"
#include <KTextEditor/Document>
#include <QMouseEvent>


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
    auto const box = mPresentation->getBox(mActiveBoxId);
    if(box != nullptr){
        box->drawBoundingBox(painter);
        box->drawScaleMarker(painter, diffToMouse);
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
        if(box->Rect().contains(mousePos)) {
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
        auto const lastAcitiveBox = mPresentation->getBox(mActiveBoxId)->Rect();
        if(!lastAcitiveBox.contains(lastPosition)){
            determineBoxInFocus(lastPosition);
        }
    }
    else{
        determineBoxInFocus(lastPosition);
    }
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    auto const posMouseBox = mPresentation->getBox(mActiveBoxId)->Rect().includePoint(lastPosition, diffToMouse);
    momentTrafo = BoxTransformation(mPresentation->getBox(mActiveBoxId), mTranform, posMouseBox, pageNumber);
    CursorApperance(lastPosition);
}

void PaintDocument::mouseDoubleClickEvent(QMouseEvent *event){
    auto const mousePos = event->pos() * mScale;
    if(mActiveBoxId.isEmpty()){
        determineBoxInFocus(mousePos);
        return;
    }
    for(auto box: mPresentation->at(pageNumber)->getBoxes()) {
        if(box->Rect().contains(mousePos) && mActiveBoxId != box->id()) {
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
    if (event->button() != Qt::LeftButton) {
        return;
    }
    momentTrafo.reset();
    update();
}


void PaintDocument::CursorApperance(QPoint mousePosition){
    auto cursor = QCursor();
    if(mActiveBoxId.isEmpty()){
        cursor.setShape(Qt::ArrowCursor);
        setCursor(cursor);
        return;
    }
    cursor.setShape(Qt::ArrowCursor);
    auto const rect = mPresentation->getBox(mActiveBoxId)->Rect();
    auto const posMouseBox = rect.includePoint(mousePosition, diffToMouse);
    switch(mTranform){
    case(TransformationType::translate):
        switch(posMouseBox){
        case pointPosition::topBorder:
            cursor.setShape(Qt::SizeVerCursor);
            break;
        case pointPosition::bottomBorder:
            cursor.setShape(Qt::SizeVerCursor);
            break;
        case pointPosition::leftBorder:
            cursor.setShape(Qt::SizeHorCursor);
            break;
        case pointPosition::rightBorder:
            cursor.setShape(Qt::SizeHorCursor);
            break;
        case pointPosition::topLeftCorner:
            cursor.setShape(Qt::SizeFDiagCursor);
            break;
        case pointPosition::bottomRightCorner:
            cursor.setShape(Qt::SizeFDiagCursor);
            break;
        case pointPosition::topRightCorner:
            cursor.setShape(Qt::SizeBDiagCursor);
            break;
        case pointPosition::bottomLeftCorner:
            cursor.setShape(Qt::SizeBDiagCursor);
            break;
        case pointPosition::inBox:
            cursor.setShape(Qt::SizeAllCursor);
            break;
        case pointPosition::notInBox:
            cursor.setShape(Qt::ArrowCursor);
        }
        break;
    case TransformationType::rotate:
        switch (posMouseBox) {
        case pointPosition::topLeftCorner:
            cursor.setShape(Qt::CrossCursor);
            break;
        case pointPosition::bottomRightCorner:
            cursor.setShape(Qt::CrossCursor);
            break;
        case pointPosition::topRightCorner:
            cursor.setShape(Qt::CrossCursor);
            break;
        case pointPosition::bottomLeftCorner:
            cursor.setShape(Qt::CrossCursor);
            break;
        case pointPosition::inBox:
            cursor.setShape(Qt::SizeAllCursor);
            break;
        default:
            cursor.setShape(Qt::ArrowCursor);
            break;
        }
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
void PaintDocument::setTransformationType(TransformationType type){
    mTranform = type;
}

