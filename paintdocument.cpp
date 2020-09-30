#include "paintdocument.h"

#include<QPainter>
#include "painter.h"

PaintDocument::PaintDocument()
    : QWidget(), aspectRatio{0.5625}, mWidth{frameSize().width()}, mSize{QSize(mWidth, mWidth*aspectRatio)}, pageNumber{0}
{
}

PaintDocument::PaintDocument(int width)
    : QWidget(), aspectRatio{0.5625}, mWidth{width}, mSize{QSize(mWidth, mWidth*aspectRatio)}, pageNumber{0}
{
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
    QPainter painter(this);
    painter.fillRect(QRect(QPoint(0, 0), mSize), Qt::white);
    painter.scale(mWidth/800., mWidth/800.);
    painter.setFont(QFont("Times", 22));
    if(!mFrames.empty()){
        auto paint = std::make_shared<Painter>(painter);
        paint->paintFrame(mFrames[pageNumber]);
    }
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

