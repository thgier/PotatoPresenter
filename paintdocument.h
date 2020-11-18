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

enum TransformationType {
    translate,
//    rotate,
    scaleTopRight,
    scaleTopLeft,
    scaleBottomLeft,
    scaleBottomRight,
    scaleTop,
    scaleBottom,
    scaleRight,
    scaleLeft
};

struct BoxTransformation{
    BoxTransformation(Box& box, TransformationType trafo)
        : mBox{box}
        , mTrafo{trafo}
    {
    }
    BoxTransformation &operator = (const BoxTransformation &b) { mTrafo = b.mTrafo; return *this; }
    Box& mBox;
    TransformationType mTrafo;
    void makeTransformation(QPoint mouseMovement){
        switch (mTrafo) {
        case TransformationType::translate:
            mBox.translateBox(mouseMovement);
            break;
        case TransformationType::scaleTopLeft:
            mBox.scaleTopLeft(mouseMovement);
            break;
        case TransformationType::scaleTopRight:
            mBox.scaleTopRight(mouseMovement);
            break;
        case TransformationType::scaleBottomLeft:
            mBox.scaleBottomLeft(mouseMovement);
            break;
        case TransformationType::scaleBottomRight:
            mBox.scaleBottomRight(mouseMovement);
            break;
        case TransformationType::scaleTop:
            mBox.scaleTop(mouseMovement);
            break;
        case TransformationType::scaleBottom:
            mBox.scaleBottom(mouseMovement);
            break;
        case TransformationType::scaleLeft:
            mBox.scaleLeft(mouseMovement);
            break;
        case TransformationType::scaleRight:
            mBox.scaleRight(mouseMovement);
            break;
        }
    }
};


class PaintDocument : public QWidget
{
public:
    PaintDocument();
    //    QSize minimumSizeHint() const override;
//    QSize sizeHint() const override;
    void setFrames(std::vector<std::shared_ptr<Frame>> frames);
    void setCurrentPage(int);
    void resizeEvent(QResizeEvent *) override;
    void createPDF();
    std::shared_ptr<Box> activeBox();
    void layoutBody();
    void layoutTitle();
    void layoutFull();
    void layoutLeft();
    void layoutRight();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
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
    TransformationType getTransformationType(QPoint mousePosition);
    int const diffToMouse = 25;
    QPainter painter;
    Layout mLayout;
    double mScale;
    int mFontSize = 50;
    QString mFont = "DejaVu Sans";
    void drawBoundingBox(QRect rect);
    void drawScaleMarker(QRect rect);
    void determineBoxInFocus(QPoint mousePos);
};

#endif // PAINTDOCUMENT_H
