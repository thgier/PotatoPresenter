#include "framewidget.h"
#include <KTextEditor/Document>
#include <QMouseEvent>
#include <QMenu>
#include<QSvgGenerator>
#include <QPainter>
#include <QDir>
#include <QShortcut>
#include "framepainter.h"
#include "imagebox.h"
#include "cachemanager.h"
#include "transformboxundo.h"

auto constexpr frameTitleSpacing = 5;

FrameWidget::FrameWidget(QWidget*&)
    : QWidget(), mPageNumber{0}, mWidth{frameSize().width()}
{
    setMouseTracking(true);
    mSize = QSize{1600, 900};
    createActions();
    recalculateGeometry();
    mTitleFont.setPixelSize(25);
}

void FrameWidget::setPresentation(std::shared_ptr<Presentation> pres){
    mPresentation = pres;
    mActiveBoxId = QString();
    mCurrentFrameId = QString();
    mPresentation->dimensions();
}

void FrameWidget::recalculateGeometry() {
    // Compute geometry of inner frame
    QPoint marginLeft = {8, 8};
    QPoint const marginRight = {15, 15};
    auto const widthOffset = marginLeft.x() + marginRight.x();
    auto const heightOffset = marginLeft.y() + marginRight.y() + QFontMetrics(mTitleFont).height() + frameTitleSpacing;

    QSize innerSize;
    auto const usableHeight = height() - heightOffset;
    auto const usableWidth = width() - widthOffset;
    if (width() * 9 / 16. > usableHeight) {
        // full height, reduced width
        auto const maxWidthForHeight = usableHeight * 16. / 9;
        innerSize = QSize(maxWidthForHeight, usableHeight);
        marginLeft.rx() += (usableWidth - maxWidthForHeight) / 2;
    }
    else {
        // full width, reduced height
        innerSize = QSize(usableWidth, usableWidth * 9 / 16.);
    }

    mGeometryDetail.mTopLeft = marginLeft;
    mGeometryDetail.mFrameSize = innerSize;
}

void FrameWidget::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.save();

    auto const marginLeft = mGeometryDetail.mTopLeft;
    auto const innerSize = mGeometryDetail.mFrameSize;

    // Draw drop shadow
    QPoint const shadowOffset = {3, 3};
    auto const shadowBasePos = marginLeft + shadowOffset;
    auto const shadowColors = {"#bbbbbb", "#cccccc", "#dddddd", "#eeeeee"};
    for (int offset = shadowColors.size()-1; offset >= 0; offset--) {
        painter.setPen(*(shadowColors.begin()+offset));
        painter.drawRect(QRect(shadowBasePos + QPoint(offset, offset), innerSize));
    }
    painter.fillRect(QRect(shadowBasePos, innerSize), "#aaaaaa");

    // Draw focus rect
    if (hasFocus()) {
        painter.setPen(this->palette().highlight().color());
    }
    else {
        painter.setPen(this->palette().mid().color());
    }
    painter.drawRect(QRect(marginLeft - QPoint(1, 1), innerSize.grownBy({1, 1, 0, 0})));

    // Done drawing the surroundings -- draw slide content now
    painter.setViewport(QRect(marginLeft, innerSize));
    painter.setWindow(QRect({0, 0}, mSize));

    mGeometryDetail.mWidgetToFrameTransform = painter.combinedTransform().inverted();

    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);

    if (mPresentation->frameList().empty()) {
        painter.restore();
        painter.end();
        return;
    }

    painter.setClipping(true);
    painter.setClipRect(QRect(QPoint(0, 0), mSize));

    FramePainter paint(painter);
    auto const frame = mPresentation->frameList().frameAt(mPageNumber);
    paint.paintFrame(frame);
    mCurrentFrameId = frame->id();

    auto const& box = mPresentation->frameList().findBox(mActiveBoxId);
    if(box != nullptr && frame->containsBox(mActiveBoxId)){
        box->drawManipulationFrame(painter, mDiffToMouse);
    }
    else{
        mActiveBoxId = QString();
    }

    // draw frame title
    painter.restore();
    painter.setFont(mTitleFont);
    auto const frameTitleRect = QRect(rect().translated(0, innerSize.height() + marginLeft.y() + frameTitleSpacing));
    painter.drawText(frameTitleRect, frame->id(), QTextOption(Qt::AlignHCenter | Qt::AlignTop));

    painter.end();
}

void FrameWidget::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->frameList().findBox(mActiveBoxId));
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

void FrameWidget::updateFrames(){
    setCurrentPage(mCurrentFrameId);
    if(mPageNumber >= int(mPresentation->frameList().vector.size())) {
        mPageNumber = int(mPresentation->frameList().vector.size()) - 1;
        mCurrentFrameId = mPresentation->frameList().vector.back()->id();
    }
    update();
}

void FrameWidget::updateFrameId() {
    mCurrentFrameId = mPresentation->frameList().frameAt(mPageNumber)->id();
}

void FrameWidget::setCurrentPage(int page){
    if(page >= int(mPresentation->frameList().numberFrames()) || page < 0) {
        return;
    }
    mPageNumber = page;
    mCurrentFrameId = mPresentation->frameList().frameAt(page)->id();
    mActiveBoxId = QString();
    Q_EMIT selectionChanged(mPresentation->frameList().frameAt(mPageNumber));
    update();
}

void FrameWidget::setCurrentPage(QString frameId){
    int counter = 0;
    for(auto const & frame: mPresentation->frameList().vector) {
        if(frame->id() == frameId) {
            mPageNumber = counter;
            break;
        }
        counter++;
    }
}

void FrameWidget::resizeEvent(QResizeEvent*) {
    mWidth = frameSize().width();
    recalculateGeometry();
}

void FrameWidget::determineBoxInFocus(QPoint mousePos){
    auto boxList = determineVisibleBoxesUnderMouse(mousePos);
    if(boxList.empty()) {
        boxList = determineBoxesUnderMouse(mousePos);
        if(boxList.empty()) {
            mActiveBoxId = "";
            return;
        }
    }
    else if (boxList.size() == 1) {
        mActiveBoxId = boxList[0];
    }
    else {
        auto currentBox = std::find(boxList.begin(), boxList.end(), mActiveBoxId);
        if(currentBox == boxList.end() || currentBox == boxList.begin()) {
            mActiveBoxId = boxList.back();
        }
        else {
            mActiveBoxId = *(currentBox - 1);
        }
    }
}

std::vector<QString> FrameWidget::determineVisibleBoxesUnderMouse(QPoint mousePos){
    std::vector<QString> boxesUnderMouse;
    for(auto &box: mPresentation->frameList().frameAt(mPageNumber)->boxes()) {
        if(box->containsPoint(mousePos, mDiffToMouse)) {
            boxesUnderMouse.push_back(box->id());
        }
    }
    return boxesUnderMouse;
}

std::vector<QString> FrameWidget::determineBoxesUnderMouse(QPoint mousePos){
    std::vector<QString> boxesUnderMouse;
    for(auto &box: mPresentation->frameList().frameAt(mPageNumber)->boxes()) {
        if(box->geometry().contains(mousePos, mDiffToMouse)) {
            boxesUnderMouse.push_back(box->id());
        }
    }
    return boxesUnderMouse;
}

void FrameWidget::mousePressEvent(QMouseEvent *event)
{
    if(mPresentation->frameList().empty()){
        return;
    }
    mMomentTrafo.reset();
    if (event->button() != Qt::LeftButton) {
        return;
    }
    mCursorLastPosition = ScaledMousePos(event);
    cursorApperance(mCursorLastPosition);
    mLastConfigFile = mPresentation->configuration();
    update();
}

void FrameWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mPresentation->frameList().empty()){
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
        if(mActiveBoxId.isEmpty() || !mPresentation->findBox(mActiveBoxId)->style().movable){
            return;
        }
        cursorApperance(newPosition);
        auto const activeBox = mPresentation->frameList().findBox(mActiveBoxId);
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

void FrameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(mPresentation->frameList().empty()){
        return;
    }
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if(mActiveBoxId.isEmpty() || !mMomentTrafo){
        determineBoxInFocus(ScaledMousePos(event));
        auto box = mPresentation->findBox(mActiveBoxId);
        if(box) {
            Q_EMIT boxSelectionChanged(box);
        }
    }
    else {
        auto transform = new TransformBoxUndo(mPresentation, mLastConfigFile, mPresentation->configuration());
        mUndoStack.push(transform);
    }
    update();
}


void FrameWidget::cursorApperance(QPoint mousePosition){
    auto cursor = QCursor();
    auto const activeBox = mPresentation->frameList().findBox(mActiveBoxId);
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

void FrameWidget::deleteBoxPosition() {
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    mPresentation->deleteBoxGeometry(mActiveBoxId, mPageNumber);
    update();
}

void FrameWidget::setActiveBox(QString boxId, QString frameId) {
    mActiveBoxId = boxId;
    mCurrentFrameId = frameId;
    updateFrames();
}

void FrameWidget::setTransformationType(TransformationType type){
    mTransform = type;
}

Qt::CursorShape FrameWidget::angleToCursor(qreal angle) const{
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

int FrameWidget::pageNumber() const{
    return mPageNumber;
}

QString const& FrameWidget::currentFrameId() const {
    return mCurrentFrameId;
}

QPoint FrameWidget::ScaledMousePos(QMouseEvent *event) const{
    return mGeometryDetail.mWidgetToFrameTransform.map(event->pos());
}

void FrameWidget::createActions(){
    openInkscape = new QAction(tr("&Open in Inkscape"), this);
    createAndOpenInkscape = new QAction(tr("&Create SVG and open in Inkscape"), this);
    connect(openInkscape, &QAction::triggered,
            this, &FrameWidget::openInInkscape);
    connect(createAndOpenInkscape, &QAction::triggered,
            this, &FrameWidget::createAndOpenSvg);

    mUndo = mUndoStack.createUndoAction(this);
    mRedo = mUndoStack.createRedoAction(this);
    mUndo->setShortcut(QKeySequence("Ctrl+Z"));
    mUndo->setShortcutContext(Qt::WidgetShortcut);
    mRedo->setShortcut(QKeySequence("Ctrl+Shift+Z"));
    mRedo->setShortcutContext(Qt::WidgetShortcut);
    this->addAction(mUndo);
    this->addAction(mRedo);
}

void FrameWidget::openInInkscape(){
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->frameList().findBox(mActiveBoxId));
    if(!image){
        return;
    }
    QString program = "/usr/bin/inkscape";
    QStringList arguments;
    arguments << image->ImagePath();
    QProcess *inkscapeProcess = new QProcess(this);
    inkscapeProcess->start(program, arguments);
}

void FrameWidget::createAndOpenSvg(){
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->frameList().findBox(mActiveBoxId));
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

void FrameWidget::undo() {
    mUndo->trigger();
}

void FrameWidget::redo() {
    mRedo->trigger();
}
