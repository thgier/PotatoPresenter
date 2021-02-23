#include "paintdocument.h"
#include <KTextEditor/Document>
#include <QMouseEvent>
#include <QMenu>
#include<QSvgGenerator>
#include <QPainter>
#include <QDir>
#include "framepainter.h"
#include "imagebox.h"
#include "cachemanager.h"

PaintDocument::PaintDocument(QWidget*&)
    : QWidget(), mPageNumber{0}, mWidth{frameSize().width()}
{
    setMouseTracking(true);
    mSize = mLayout.mSize;
    mScale = 1.0 * mSize.width() / mWidth;
    createActions();
}

void PaintDocument::setPresentation(std::shared_ptr<Presentation> pres){
    mPresentation = pres;
    mActiveBoxId = QString();
    mCurrentFrameId = QString();
    mLayout = mPresentation->layout();
    mSize = mLayout.mSize;
    mScale = 1.0 * mSize.width() / mWidth;
}

void PaintDocument::paintEvent(QPaintEvent*)
{
    mPainter.begin(this);
    mPainter.setViewport(QRect(0, 0, mWidth, 1.0 * mWidth/mSize.width()*mSize.height()));
    mPainter.setWindow(QRect(QPoint(0, 0), mSize));
    mPainter.setRenderHint(QPainter::SmoothPixmapTransform);
    mPainter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);
    if(!mPresentation->empty()){
        FramePainter paint(mPainter);
        paint.paintFrame(mPresentation->frameAt(mPageNumber));
        mCurrentFrameId = mPresentation->frameAt(mPageNumber)->id();
    }
    auto const box = mPresentation->findBox(mActiveBoxId);
    if(box != nullptr && mPresentation->findFrame(mCurrentFrameId)->containsBox(mActiveBoxId)){
        box->drawSelectionFrame(mPainter);
        box->drawScaleHandle(mPainter, mDiffToMouse);
    }
    else{
        mActiveBoxId = QString();
    }
    auto font = mPainter.font();
    font.setPixelSize(50);
    mPainter.setFont(font);
    mPainter.drawText(QRect(0, mSize.height(), mSize.width(), 80), Qt::AlignCenter, mCurrentFrameId);
    mPainter.end();
}

QSize PaintDocument::sizeHint() const{
    return mLayout.mSize;
}

void PaintDocument::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->findBox(mActiveBoxId));
    if(image){
        auto const imagePath = image->ImagePath();
        if(QFile::exists(imagePath)){
            menu.addAction(openInkscape);
        }
        else{
            menu.addAction(createAndOpenInkscape);
        }
    }
    menu.exec(event->globalPos());
}

void PaintDocument::updateFrames(){
    setCurrentPage(mCurrentFrameId);
    update();
}

void PaintDocument::setCurrentPage(int page){
    if(page >= int(mPresentation->numberFrames()) || page < 0) {
        return;
    }
    mPageNumber = page;
    mCurrentFrameId = mPresentation->frameAt(page)->id();
    mActiveBoxId = QString();
    Q_EMIT selectionChanged(mPresentation->frameAt(mPageNumber));
    update();
}

void PaintDocument::setCurrentPage(QString frameId){
    int counter = 0;
    for(auto const & frame: mPresentation->frames()) {
        if(frame->id() == frameId) {
            if(mPageNumber != counter){
                mActiveBoxId = QString();
            }
            mPageNumber = counter;
            Q_EMIT pageNumberChanged(mPageNumber);
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
    auto lastId = mActiveBoxId;
    mActiveBoxId = QString();
    for(auto box: mPresentation->frameAt(mPageNumber)->boxes()) {
        if(box->geometry().contains(mousePos) && lastId != box->id()) {
            mActiveBoxId = box->id();
            break;
        }
    }
}

Box::List PaintDocument::determineBoxesUnderMouse(QPoint mousePos){
    mActiveBoxId = QString();
    Box::List boxesUnderMouse;
    for(auto &box: mPresentation->frameAt(mPageNumber)->boxes()) {
        if(box->geometry().contains(mousePos, mDiffToMouse)) {
            boxesUnderMouse.push_back(box);
        }
    }
    return boxesUnderMouse;
}

void PaintDocument::mousePressEvent(QMouseEvent *event)
{
    if(mPresentation->empty()){
        return;
    }
    mMomentTrafo.reset();
    if (event->button() != Qt::LeftButton) {
        return;
    }
    mCursorLastPosition = ScaledMousePos(event);
    cursorApperance(mCursorLastPosition);
    update();
}

void PaintDocument::mouseMoveEvent(QMouseEvent *event)
{
    if(mPresentation->empty()){
        return;
    }
    auto const newPosition = ScaledMousePos(event);
    if(event->buttons() != Qt::LeftButton){
        cursorApperance(newPosition);
        return;
    }
    auto const mouseMovement = newPosition - mCursorLastPosition;
    if(mouseMovement.manhattanLength() < mDiffToMouse / 5){
        return;
    }
    if(!mMomentTrafo){
        cursorApperance(newPosition);
        if(mActiveBoxId.isEmpty()){
            return;
        }
        auto const activeBox = mPresentation->findBox(mActiveBoxId);
        auto const clasifiedMousePos = activeBox->geometry().classifyPoint(mCursorLastPosition, mDiffToMouse);
        if(clasifiedMousePos == pointPosition::notInBox){
            mActiveBoxId = QString();
            return;
        }
        mMomentTrafo = BoxTransformation(activeBox, mTransform, clasifiedMousePos, mPageNumber, newPosition);
    }
    mMomentTrafo->doTransformation(newPosition, mPresentation);
    mCursorLastPosition = newPosition;
    update();
}

void PaintDocument::mouseReleaseEvent(QMouseEvent *event)
{
    if(mPresentation->empty()){
        return;
    }
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if(mActiveBoxId.isEmpty() || !mMomentTrafo){
        determineBoxInFocus(ScaledMousePos(event));
    }
    update();
}


void PaintDocument::cursorApperance(QPoint mousePosition){
    auto cursor = QCursor();
    auto const activeBox = mPresentation->findBox(mActiveBoxId);
    if(!activeBox){
        cursor.setShape(Qt::ArrowCursor);
        setCursor(cursor);
        return;
    }
    cursor.setShape(Qt::ArrowCursor);
    auto const rect = activeBox->geometry();
    auto const posMouseBox = rect.classifyPoint(mousePosition, mDiffToMouse);
    auto angle = rect.angle();
    switch(mTransform){
    case(TransformationType::translate):
        switch(posMouseBox){
        case pointPosition::topBorder:
            cursor.setShape(angleToCursor(90 + angle));
            break;
        case pointPosition::bottomBorder:
            cursor.setShape(angleToCursor(270 + angle));
            break;
        case pointPosition::leftBorder:
            cursor.setShape(angleToCursor(angle));
            break;
        case pointPosition::rightBorder:
            cursor.setShape(angleToCursor(180 + angle));
            break;
        case pointPosition::topLeftCorner:
            cursor.setShape(angleToCursor(45 + angle));
            break;
        case pointPosition::bottomRightCorner:
            cursor.setShape(angleToCursor(225 + angle));
            break;
        case pointPosition::topRightCorner:
            cursor.setShape(angleToCursor(135 + angle));
            break;
        case pointPosition::bottomLeftCorner:
            cursor.setShape(angleToCursor(315 + angle));
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

void PaintDocument::layoutTitle(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mTitlePos, mPageNumber);
    update();
}

void PaintDocument::layoutBody(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mBodyPos, mPageNumber);
    update();
}

void PaintDocument::layoutFull(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mFullPos, mPageNumber);
    update();
}

void PaintDocument::layoutLeft(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mLeftPos, mPageNumber);
    update();
}

void PaintDocument::layoutRight(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mRightPos, mPageNumber);
    update();
}

void PaintDocument::layoutPresTitle(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mPresTitlePos, mPageNumber);
    update();
}

void PaintDocument::layoutSubtitle(){
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->setBoxGeometry(mActiveBoxId, mLayout.mSubtitlePos, mPageNumber);
    update();
}
void PaintDocument::setTransformationType(TransformationType type){
    mTransform = type;
}

Qt::CursorShape PaintDocument::angleToCursor(qreal angle) const{
    angle = int(angle) % 180;
    if(angle >= 157.5 || angle < 22.5){
        return Qt::SizeHorCursor;
    }
    if(angle >= 22.5 && angle < 67.5){
        return Qt::SizeFDiagCursor;
    }
    if(angle >= 67.5 && angle < 112.5){
        return Qt::SizeVerCursor;
    }
    if(angle >= 110.5 && angle < 157.5){
        return Qt::SizeBDiagCursor;
    }
    else{
        return Qt::SizeAllCursor;
    }
}

int PaintDocument::pageNumber() const{
    return mPageNumber;
}

QPoint PaintDocument::ScaledMousePos(QMouseEvent *event) const{
    return event->pos() * mScale;
}

void PaintDocument::createActions(){
    openInkscape = new QAction(tr("&open in Inkscape"), this);
    createAndOpenInkscape = new QAction(tr("&create Svg and open in Inkscape"), this);
    connect(openInkscape, &QAction::triggered,
            this, &PaintDocument::openInInkscape);
    connect(createAndOpenInkscape, &QAction::triggered,
            this, &PaintDocument::createAndOpenSvg);
}

void PaintDocument::openInInkscape(){
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->findBox(mActiveBoxId));
    if(!image){
        return;
    }
    QString program = "/usr/bin/inkscape";
    QStringList arguments;
    arguments << image->ImagePath();
    QProcess *inkscapeProcess = new QProcess(this);
    inkscapeProcess->start(program, arguments);
}

void PaintDocument::createAndOpenSvg(){
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->findBox(mActiveBoxId));
    if(!image){
        return;
    }
    QDir().mkpath(QFileInfo(image->ImagePath()).absolutePath());
    CacheManager<QSvgRenderer>::instance().deleteFile(image->ImagePath());
    QSvgGenerator generator;
    generator.setFileName(image->ImagePath());
    generator.setSize(image->geometry().rect().size());
    generator.setViewBox(QRect(QPoint(0, 0), image->geometry().rect().size()));
    QPainter painter;
    painter.begin(&generator);
    painter.end();
    update();
    openInInkscape();
}
