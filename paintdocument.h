#ifndef PAINTDOCUMENT_H
#define PAINTDOCUMENT_H

#include <QWidget>
#include <vector>
#include <QSize>
#include <KTextEditor/Document>
#include <QMouseEvent>
#include <QPdfWriter>
#include <QPrinter>
#include "frame.h"
#include "parser.h"
#include "layout.h"

enum TransformationTyp {
    translate,
//    rotate,
    scaleTopRight,
    scaleTopLeft,
    scaleBottomLeft,
    scaleBottomRight,
};

struct BoxTransformation{
    BoxTransformation(Box& box, TransformationTyp trafo)
        : mBox{box}
        , mTrafo{trafo}
    {
    }
    BoxTransformation &operator = (const BoxTransformation &b) { mTrafo = b.mTrafo; return *this; }
    Box& mBox;
    TransformationTyp mTrafo;
    void makeTransformation(QPoint mouseMovement){
        mBox.setBoundingBoxVisible(true);
        switch (mTrafo) {
        case TransformationTyp::translate:
            mBox.translateBox(mouseMovement);
            break;
        case TransformationTyp::scaleTopLeft:
            mBox.scaleTopLeft(mouseMovement);
            break;
        case TransformationTyp::scaleTopRight:
            mBox.scaleTopRight(mouseMovement);
            break;
        case TransformationTyp::scaleBottomLeft:
            mBox.scaleBottomLeft(mouseMovement);
            break;
        case TransformationTyp::scaleBottomRight:
            mBox.scaleBottomRight(mouseMovement);
            break;
        }
    }
};


class PaintDocument : public QWidget
{
public:
    PaintDocument();
    PaintDocument(int width);
    //    QSize minimumSizeHint() const override;
//    QSize sizeHint() const override;
    void setFrames(std::vector<std::shared_ptr<Frame>> frames);
    void setCurrentPage(int);
    void resizeEvent(QResizeEvent *) override;
    void createPDF();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    double aspectRatio;
    int mWidth;
    void paintEvent(QPaintEvent *event) override;
    std::vector<std::shared_ptr<Frame>> mFrames;
    QSize mSize;
    int pageNumber;
private:
    bool move = false;
    bool scale = false;
    QPoint lastPosition;
    std::optional<BoxTransformation> momentTrafo;
    std::shared_ptr<Box> mBoxInFocus;
    void CursorApperance(QPoint mousePosition);
    TransformationTyp getTransformationType(QPoint mousePosition);
    int const diffToMouse = 20 * (800./mWidth);
    QPainter painter;
    Layout mLayout;
};

#endif // PAINTDOCUMENT_H
