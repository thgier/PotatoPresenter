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

namespace {
std::vector<int> boxesToXGuides(Box::List boxes) {
    std::vector<int> guides;
    for(auto const& box: boxes) {
        guides.push_back(box->geometry().left());
        guides.push_back(box->geometry().rect().right());
    }
    return guides;
}

std::vector<int> boxesToYGuides(Box::List boxes) {
    std::vector<int> guides;
    for(auto const& box: boxes) {
        guides.push_back(box->geometry().top());
        guides.push_back(box->geometry().rect().bottom());
    }
    return guides;
}
}

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
    mUndoStack.clear();
    update();
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

    // draw Guides for Snapping
    if(mCurrentTrafo) {
        painter.save();
        painter.setPen("#999");
        if(mCurrentTrafo->snapToMiddle()) {
            auto const textRect = QRect(mSize.width() / 2, 20, 140, 20);
            painter.fillRect(textRect, "#ddd");
            painter.setPen(Qt::black);
            painter.setFont(QFont("sans-serif", 10));
            painter.drawText(textRect, "Snap to middle");
            painter.setPen("#777");
        }
        if(mCurrentTrafo->xGuide()) {
            auto const x = mCurrentTrafo->xGuide().value();
            painter.drawLine(x, 0, x, mSize.height());
        }
        if(mCurrentTrafo->yGuide()) {
            auto const y = mCurrentTrafo->yGuide().value();
            painter.drawLine(0, y, mSize.width(), y);
        }
        painter.restore();
    }

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
        auto const imagePath = absoluteImagePath(image->ImagePath());
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
    if(mPresentation->frameList().vector.empty()) {
        mCurrentFrameId = "";
        return;
    }
    if(mPageNumber >= int(mPresentation->frameList().vector.size())) {
        mPageNumber = mPresentation->frameList().vector.size() - 1;
    }
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
    if (boxList.size() == 1) {
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
    mCurrentTrafo.reset();
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
    auto boxInFocus = mPresentation->findBox(mActiveBoxId);
    if(!mCurrentTrafo){
        if(mActiveBoxId.isEmpty() || !boxInFocus->style().movable){
            return;
        }
        cursorApperance(newPosition);
        auto const classifiedMousePos = boxInFocus->geometry().classifyPoint(mCursorLastPosition, mDiffToMouse);
        if(classifiedMousePos == pointPosition::notInBox){
            mActiveBoxId = QString();
            return;
        }
        mCurrentTrafo = BoxTransformation(boxInFocus->geometry(), mTransform, classifiedMousePos, newPosition);
        if(mSnapping) {
            auto boxesWithoutActive = mPresentation->frameList().vector[mPageNumber]->boxes();
            std::erase_if(boxesWithoutActive, [this](auto a){return a->id() == mActiveBoxId;});
            auto xSnapGuides = boxesToXGuides(boxesWithoutActive);
            xSnapGuides.push_back(0);
            xSnapGuides.push_back(mSize.width());
            auto ySnapGuides = boxesToYGuides(boxesWithoutActive);
            ySnapGuides.push_back(0);
            ySnapGuides.push_back(mSize.height());
            mCurrentTrafo->setSnapping({xSnapGuides, ySnapGuides, {mSize.width() / 2}, mDiffToMouse});
        }
    }
    auto transformedRect = mCurrentTrafo->doTransformation(newPosition);
    mPresentation->setBoxGeometry(mActiveBoxId, transformedRect, mPageNumber);
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
    if(mActiveBoxId.isEmpty() || !mCurrentTrafo){
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
    mCurrentTrafo.reset();
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
    arguments << absoluteImagePath(image->ImagePath());
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
    generator.setFileName(absoluteImagePath(image->ImagePath()));
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
    qInfo() << "undo";
}

void FrameWidget::redo() {
    mRedo->trigger();
}

void FrameWidget::setSnapping(bool snapping) {
    mSnapping = snapping;
}

QString FrameWidget::absoluteImagePath(QString imagePath) const {
    if(!imagePath.startsWith("/home")) {
        auto variables = mPresentation->frameList().vector[mPageNumber]->variables();
        auto it = variables.find("%{resourcepath}");
        if(it != variables.end()) {
            imagePath = it->second + "/" + imagePath;
        }
    }
    return imagePath;
}
