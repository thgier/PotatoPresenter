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

void PaintDocument::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPosition = event->pos();
        for(auto box: mFrames[pageNumber]->getBoxes()) {
            if(box->Rect().contains(lastPosition)) {
                move = true;
                movedBox = box;
                movedBox->setBoundingBox(true);
                break;
            }
        }
    }
}

void PaintDocument::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && move) {
        auto const newPosition = event->pos();
        movedBox->translateBox(newPosition - lastPosition);
        lastPosition = newPosition;
        update();
    }
}

void PaintDocument::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && move) {
//        TODO: maybe translate again
        move = false;
        movedBox->setBoundingBox(false);
    }
}

std::vector<std::shared_ptr<Box>> PaintDocument::getBoxes(std::vector<std::shared_ptr<Frame>> frames){
    std::vector<std::shared_ptr<Box>> boxes = {};
    for (auto frame : frames) {
        auto const frameBoxes = frame->getBoxes();
        boxes.insert(boxes.end(), frameBoxes.begin(), frameBoxes.end());
    }
    return boxes;
}

std::vector<std::shared_ptr<Box>> PaintDocument::getBoxes(){
    return getBoxes(mFrames);
}

void PaintDocument::updateFrames(std::vector<std::shared_ptr<Frame> > frames){
    if(mFrames.empty()){
        setFrames(frames);
    }
    else{
        auto boxes = getBoxes();
        setFrames(frames);
        for (auto frame: frames) {
            for (auto box : frame->getBoxes()) {
                for(auto oldBox: boxes){
                    if(oldBox->id() == box->id()){
                        box->setRect(oldBox->Rect());
                        break;
                    }
                }
            }

        }
        mFrames = frames;
    }
}
