#include "paintdocument.h"

#include<QPainter>
#include "painter.h"

PaintDocument::PaintDocument()
    : QWidget(), aspectRatio{210./297}, mWidth{frameSize().width()}, mSize{QSize(mWidth, mWidth*aspectRatio)}
    , pageNumber{0}, mLayout{Layout(aspectRatio::sixteenToNine)}
{
    setMouseTracking(true);
}

PaintDocument::PaintDocument(int width)
    : QWidget(), aspectRatio{0.5625}, mWidth{width}, mSize{QSize(mWidth, mWidth*aspectRatio)}
    , pageNumber{0}, mLayout{Layout(aspectRatio::sixteenToNine)}
{
    setMouseTracking(true);
}

//QSize PaintDocument::sizeHint() const
//{
//    return mSize;
//}

//QSize PaintDocument::minimumSizeHint() const
//{
//    return QSize(100, 100);
//}

void PaintDocument::paintEvent(QPaintEvent*)
{
    painter.begin(this);
    painter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);
    painter.scale(mWidth/800., mWidth/800.);
    painter.setFont(QFont("Times", 22));
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
    mSize = QSize(mWidth, mWidth*aspectRatio);
}

void PaintDocument::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    lastPosition = event->pos() * (800./mWidth);
    if(mBoxInFocus != NULL){
        mBoxInFocus->setBoundingBoxVisible(false);
    }
    for(auto box: mFrames[pageNumber]->getBoxes()) {
        auto const boxMargins = box->Rect().marginsAdded(QMargins(diffToMouse, diffToMouse, diffToMouse, diffToMouse));
        if(boxMargins.contains(lastPosition)) {
            mBoxInFocus = box;
            auto const trafoType = getTransformationType(lastPosition);
            qWarning() << "trafotype" << trafoType;
            momentTrafo = BoxTransformation(*box.get(), trafoType);
            CursorApperance(lastPosition);
            mBoxInFocus->setBoundingBoxVisible(true);
            break;
        }
    }

}

void PaintDocument::mouseMoveEvent(QMouseEvent *event)
{
    CursorApperance(event->pos() * (800./mWidth));
    if ((event->buttons() & Qt::LeftButton)) {
        auto const newPosition = event->pos() * (800./mWidth);
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

TransformationTyp PaintDocument::getTransformationType(QPoint mousePosition){
    if(mBoxInFocus == NULL){
        return {};
    }
    auto cursor = QCursor();
    auto const rect = mBoxInFocus->Rect();
    TransformationTyp type = {};
    if((rect.topLeft() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationTyp::scaleTopLeft;
        cursor.setShape(Qt::SizeFDiagCursor);
    }
    else if((rect.topRight() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationTyp::scaleTopRight;
        cursor.setShape(Qt::SizeBDiagCursor);
    }
    else if((rect.bottomLeft() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationTyp::scaleBottomLeft;
        cursor.setShape(Qt::SizeBDiagCursor);
    }
    else if((rect.bottomRight() - mousePosition).manhattanLength() < diffToMouse){
        type = TransformationTyp::scaleBottomRight;
        cursor.setShape(Qt::SizeFDiagCursor);
    }
    else if(rect.contains(mousePosition)){
        type = TransformationTyp::translate;
        cursor.setShape(Qt::ArrowCursor);
    }
    setCursor(cursor);
    return type;
}

void PaintDocument::CursorApperance(QPoint mousePosition){
    auto cursor = QCursor();
        if(mBoxInFocus == NULL){
        return;
    }
    auto const rect = mBoxInFocus->Rect();
    if((rect.topLeft() - mousePosition).manhattanLength() < diffToMouse || (rect.bottomRight() - mousePosition).manhattanLength() < diffToMouse){
        cursor.setShape(Qt::SizeFDiagCursor);
    }
    else if((rect.topRight() - mousePosition).manhattanLength() < diffToMouse || (rect.bottomLeft() - mousePosition).manhattanLength() < diffToMouse) {
        cursor.setShape(Qt::SizeBDiagCursor);
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
//    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageSize(QPageSize(QSize(1600, 900)));
    auto const resolution = pdfWriter.resolution();
    auto const size = pdfWriter.pageLayout().paintRectPixels(resolution);
//    pdfWriter.setPageOrientation(QPageLayout::Landscape);
//    auto const scale = width / 800.;
    QPainter painter(&pdfWriter);

    painter.save();
    painter.begin(this);
    painter.fillRect(QRect(size), Qt::blue);
    scale = size.width() / 800.;
    painter.fillRect(0, 0, 800, 200, Qt::green);
    painter.scale(scale, scale);
    painter.fillRect(0, 0, 800, 100, Qt::yellow);
//    painter.setFont(QFont("Times", 22));
//    painter.drawText(QPoint(100, 50), "Hallo");
    for(auto frame: mFrames){
        auto paint = std::make_shared<Painter>(painter);
        paint->paintFrame(frame);
        pdfWriter.newPage();
    }
    painter.restore();
}
