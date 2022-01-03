/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "slidewidget.h"
#include <KTextEditor/Document>
#include <QMouseEvent>
#include <QMenu>
#include<QSvgGenerator>
#include <QPainter>
#include <QDir>
#include <QShortcut>
#include <QMessageBox>
#include "sliderenderer.h"
#include "imagebox.h"
#include "cachemanager.h"
#include "transformboxundo.h"

namespace {
std::vector<int> boxesToXGuides(Box::List boxes) {
    std::vector<int> guides;
    for(auto const& box: boxes) {
        guides.push_back(box->geometry().leftDisplay());
    }
    return guides;
}

std::vector<int> boxesToYGuides(Box::List boxes) {
    std::vector<int> guides;
    for(auto const& box: boxes) {
        guides.push_back(box->geometry().topDisplay());
    }
    return guides;
}
}

auto constexpr slideTitleSpacing = 5;

SlideWidget::SlideWidget(QWidget*&)
    : QWidget(), mPageNumber{0}, mWidth{frameSize().width()}
{
    setMouseTracking(true);
    mSize = QSize{1600, 900};
    createActions();
    recalculateGeometry();
    mTitleFont.setPixelSize(25);
}

void SlideWidget::setPresentation(std::shared_ptr<Presentation> pres){
    mPresentation = pres;
    mActiveBoxId = QString();
    mCurrentSlideId = QString();
    connect(mPresentation.get(), &Presentation::slideChanged,
            this, QOverload<>::of(&SlideWidget::update));
    mUndoStack.clear();
    update();
}

void SlideWidget::recalculateGeometry() {
    // Compute geometry of inner slide
    QPoint marginLeft = {8, 8};
    QPoint const marginRight = {15, 15};
    auto const widthOffset = marginLeft.x() + marginRight.x();
    auto const heightOffset = marginLeft.y() + marginRight.y() + QFontMetrics(mTitleFont).height() + slideTitleSpacing;

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
    mGeometryDetail.mSlideSize = innerSize;
}

void SlideWidget::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.save();

    auto const marginLeft = mGeometryDetail.mTopLeft;
    auto const innerSize = mGeometryDetail.mSlideSize;

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
    auto grownSize = innerSize;
    grownSize.rwidth() += 1;
    grownSize.rheight() += 1;
    painter.drawRect(QRect(marginLeft - QPoint(1, 1), grownSize));

    // Done drawing the surroundings -- draw slide content now
    painter.setViewport(QRect(marginLeft, innerSize));
    painter.setWindow(QRect({0, 0}, mSize));

    mGeometryDetail.mWidgetToSlideTransform = painter.combinedTransform().inverted();

    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);

    if (mPresentation->slideList().empty()) {
        painter.restore();
        painter.end();
        return;
    }

    painter.setClipping(true);
    painter.setClipRect(QRect(QPoint(0, 0), mSize));

    SlideRenderer paint(painter);
    auto const slide = mPresentation->data().slideListDefaultApplied().slideAt(mPageNumber);
    paint.paintSlide(slide);
    mCurrentSlideId = slide->id();

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

    auto const& box = mPresentation->findBox(mActiveBoxId);
    if(box != nullptr && slide->containsBox(mActiveBoxId)){
        box->drawManipulationSlide(painter, mDiffToMouse);
    }
    else{
        mActiveBoxId = QString();
    }

    // draw slide title
    painter.restore();
    painter.setFont(mTitleFont);
    auto const slideTitleRect = QRect(rect().translated(0, innerSize.height() + marginLeft.y() + slideTitleSpacing));
    painter.drawText(slideTitleRect, slide->id(), QTextOption(Qt::AlignHCenter | Qt::AlignTop));

    painter.end();
}

void SlideWidget::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.addAction(mUndo);
    menu.addAction(mRedo);
    menu.addAction(mResetBox);
    menu.addAction(mResetAngle);
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->findBox(mActiveBoxId));
    if(image){
        auto const imagePath = absoluteImagePath(image->ImagePath());
        if(QFile::exists(imagePath)){
            menu.addAction(mOpenInkscape);
        }
        else{
            menu.addAction(mCreateAndOpenInkscape);
        }
    }
    menu.exec(event->globalPos());
}

void SlideWidget::updateSlides(){
    setCurrentPage(mCurrentSlideId);
    if(mPageNumber >= int(mPresentation->slideList().vector.size())) {
        mPageNumber = int(mPresentation->slideList().vector.size()) - 1;
        mCurrentSlideId = mPresentation->slideList().vector.back()->id();
    }
    update();
}

void SlideWidget::updateSlideId() {
    if(mPresentation->slideList().vector.empty()) {
        mCurrentSlideId = "";
        return;
    }
    if(mPageNumber >= int(mPresentation->slideList().vector.size())) {
        mPageNumber = mPresentation->slideList().vector.size() - 1;
    }
    mCurrentSlideId = mPresentation->slideList().slideAt(mPageNumber)->id();
}

void SlideWidget::setCurrentPage(int page){
    if(page >= int(mPresentation->slideList().numberSlides()) || page < 0) {
        return;
    }
    mPageNumber = page;
    mCurrentSlideId = mPresentation->slideList().slideAt(page)->id();
    mActiveBoxId = QString();
    Q_EMIT selectionChanged(mPresentation->slideList().slideAt(mPageNumber));
    update();
}

void SlideWidget::setCurrentPage(QString slideId){
    int counter = 0;
    for(auto const & slide: mPresentation->slideList().vector) {
        if(slide->id() == slideId) {
            mPageNumber = counter;
            break;
        }
        counter++;
    }
}

void SlideWidget::resizeEvent(QResizeEvent*) {
    mWidth = frameSize().width();
    recalculateGeometry();
}

void SlideWidget::determineBoxInFocus(QPoint mousePos){
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

std::vector<QString> SlideWidget::determineVisibleBoxesUnderMouse(QPoint mousePos){
    std::vector<QString> boxesUnderMouse;
    for(auto &box: mPresentation->slideList().slideAt(mPageNumber)->boxes()) {
        if(box->containsPoint(mousePos, mDiffToMouse)) {
            boxesUnderMouse.push_back(box->id());
        }
    }
    return boxesUnderMouse;
}

std::vector<QString> SlideWidget::determineBoxesUnderMouse(QPoint mousePos){
    std::vector<QString> boxesUnderMouse;
    for(auto &box: mPresentation->slideList().slideAt(mPageNumber)->boxes()) {
        if(box->geometry().contains(mousePos, mDiffToMouse)) {
            boxesUnderMouse.push_back(box->id());
        }
    }
    return boxesUnderMouse;
}

void SlideWidget::mousePressEvent(QMouseEvent *event)
{
    if(mPresentation->slideList().empty()){
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

void SlideWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mPresentation->slideList().empty()){
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
            auto boxesWithoutActive = mPresentation->slideList().vector[mPageNumber]->boxes();
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
}

void SlideWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(mPresentation->slideList().empty()){
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

void SlideWidget::keyPressEvent(QKeyEvent *event) {
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    QPoint translation;
    switch (event->key()) {
        case Qt::Key_Left:
        translation = QPoint(-1, 0);
        break;
        case Qt::Key_Right:
        translation = QPoint(1, 0);
        break;
        case Qt::Key_Down:
        translation = QPoint(0, 1);
        break;
        case Qt::Key_Up:
        translation = QPoint(0, -1);
        break;
        case Qt::Key_Escape:
        mActiveBoxId = "";
        update();
        return;
    }

    auto geometry = mPresentation->findBox(mActiveBoxId)->geometry();
    auto rect = geometry.rect();
    rect.translate(translation * 2);
    geometry.setRect(rect);
    mPresentation->setBoxGeometry(mActiveBoxId, geometry, mPageNumber);
}


void SlideWidget::cursorApperance(QPoint mousePosition) {
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
    auto angle = rect.angleDisplay();
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
            cursor = QCursor({":/icons/rotate.png"});
            break;
        case pointPosition::bottomRightCorner:
            cursor = QCursor({":/icons/rotate.png"});
            break;
        case pointPosition::topRightCorner:
            cursor = QCursor({":/icons/rotate.png"});
            break;
        case pointPosition::bottomLeftCorner:
            cursor = QCursor({":/icons/rotate.png"});
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

void SlideWidget::deleteBoxPosition() {
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    auto const lastConfig = mPresentation->configuration();
    mPresentation->deleteBoxGeometry(mActiveBoxId, mPageNumber);
    auto transform = new TransformBoxUndo(mPresentation, lastConfig, mPresentation->configuration());
    mUndoStack.push(transform);
}

void SlideWidget::deleteBoxAngle() {
    if(mActiveBoxId.isEmpty()) {
        return;
    }
    auto const lastConfig = mPresentation->configuration();
    mPresentation->deleteBoxAngle(mActiveBoxId, mPageNumber);
    auto transform = new TransformBoxUndo(mPresentation, lastConfig, mPresentation->configuration());
    mUndoStack.push(transform);
}

void SlideWidget::setActiveBox(QString boxId, QString slideId) {
    mActiveBoxId = boxId;
    mCurrentSlideId = slideId;
    updateSlides();
}

void SlideWidget::setTransformationType(TransformationType type){
    mTransform = type;
}

Qt::CursorShape SlideWidget::angleToCursor(qreal angle) const{
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

int SlideWidget::pageNumber() const{
    return mPageNumber;
}

QString const& SlideWidget::currentSlideId() const {
    return mCurrentSlideId;
}

QPoint SlideWidget::ScaledMousePos(QMouseEvent *event) const{
    return mGeometryDetail.mWidgetToSlideTransform.map(event->pos());
}

void SlideWidget::createActions(){
    // Undo, Redo
    mUndo = mUndoStack.createUndoAction(this);
    mRedo = mUndoStack.createRedoAction(this);
    mUndo->setShortcut(QKeySequence("Ctrl+Z"));
    mUndo->setShortcutContext(Qt::WidgetShortcut);
    mRedo->setShortcut(QKeySequence("Ctrl+Shift+Z"));
    mRedo->setShortcutContext(Qt::WidgetShortcut);
    this->addAction(mUndo);
    this->addAction(mRedo);

    // reset Box position
    mResetBox = new QAction(tr("Reset Position"), this);
    mResetBox->setIcon(QIcon::fromTheme("edit-reset"));
    connect(mResetBox, &QAction::triggered,
            this, &SlideWidget::deleteBoxPosition);
    mResetAngle = new QAction(tr("Reset Rotation"), this);
    mResetAngle->setIcon(QIcon::fromTheme("chronometer-reset"));
    connect(mResetAngle, &QAction::triggered,
            this, &SlideWidget::deleteBoxAngle);

    // open in inkscape
    mOpenInkscape = new QAction(tr("&Open in Inkscape"), this);
    mCreateAndOpenInkscape = new QAction(tr("&Create SVG and open in Inkscape"), this);
    connect(mOpenInkscape, &QAction::triggered,
            this, &SlideWidget::openInInkscape);
    connect(mCreateAndOpenInkscape, &QAction::triggered,
            this, &SlideWidget::createAndOpenSvg);

}

void SlideWidget::openInInkscape(){
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->findBox(mActiveBoxId));
    if(!image){
        return;
    }
    QString program = "/usr/bin/inkscape";
    QStringList arguments;
    arguments << absoluteImagePath(image->ImagePath());
    QProcess *inkscapeProcess = new QProcess(this);
    auto success = inkscapeProcess->startDetached(program, arguments);
    if(!success) {
        QMessageBox::information(this, tr("Cannot open Inkscape."), tr("Cannot open Inkscape. Make sure Inkscape is installed."),
                                         QMessageBox::Ok);
    }
}

void SlideWidget::createAndOpenSvg(){
    auto const image = std::dynamic_pointer_cast<ImageBox>(mPresentation->findBox(mActiveBoxId));
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

void SlideWidget::undo() {
    mUndo->trigger();
    qInfo() << "undo";
}

void SlideWidget::redo() {
    mRedo->trigger();
}

void SlideWidget::setSnapping(bool snapping) {
    mSnapping = snapping;
}

QString SlideWidget::absoluteImagePath(QString imagePath) const {
    if(!imagePath.startsWith("/home")) {
        auto variables = mPresentation->slideList().vector[mPageNumber]->variables();
        auto it = variables.find("%{resourcepath}");
        if(it != variables.end()) {
            imagePath = it->second + "/" + imagePath;
        }
    }
    return imagePath;
}

QUndoStack& SlideWidget::undoStack() {
    return mUndoStack;
}
