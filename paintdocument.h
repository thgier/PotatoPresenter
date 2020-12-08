#ifndef PAINTDOCUMENT_H
#define PAINTDOCUMENT_H

#include <QWidget>
#include <vector>
#include <QSize>
#include <KTextEditor/Document>
#include <QMouseEvent>
#include <QPdfWriter>
#include <QPrinter>
#include <QDebug>
#include <QObject>
#include "frame.h"
#include "parser.h"
#include "layout.h"
#include "equationcachemanager.h"
#include "presentation.h"

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
    BoxTransformation(std::shared_ptr<Box> box, TransformationType trafo, int pageNumber)
        : mBox{box}
        , mTrafo{trafo}
        , mPageNumber{pageNumber}
    {
    }
    BoxTransformation &operator = (const BoxTransformation &b) { mTrafo = b.mTrafo; return *this; }
    std::shared_ptr<Box> mBox;
    TransformationType mTrafo;
    int mPageNumber;
    void makeTransformation(QPoint mouseMovement, Presentation* pres){
        auto rect = mBox->Rect();
        switch (mTrafo) {
        case TransformationType::translate:{
            rect.translate(mouseMovement);
            break;
        }
        case TransformationType::scaleTopLeft:{
            auto const point = rect.bottomRight();
            auto const width = rect.width() - mouseMovement.x();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveBottomRight(point);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleTopRight:{
            auto const point = rect.bottomLeft();
            auto const width = rect.width() + mouseMovement.x();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveBottomLeft(point);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleBottomLeft:{
            auto const point = rect.topRight();
            auto const width = rect.width() - mouseMovement.x();
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveTopRight(point);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleBottomRight:{
            auto const point = rect.topLeft();
            auto const width = rect.width() + mouseMovement.x();
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveTopLeft(point);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleTop:{
            auto const point = rect.bottomLeft();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setHeight(heigth);
            rect.moveBottomLeft(point);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleBottom:{
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setHeight(heigth);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleLeft:{
            auto const point = rect.topRight();
            auto const width = rect.width() - mouseMovement.x();
            rect.setWidth(width);
            rect.moveTopRight(point);
            rect = rect.normalized();
            break;
        }
        case TransformationType::scaleRight:{
            auto const width = rect.width() + mouseMovement.x();
            rect.setWidth(width);
            rect = rect.normalized();
            break;
        }
        }
        pres->setBox(mBox->id(), rect, mPageNumber);
    }
};


class PaintDocument : public QWidget
{
    Q_OBJECT
public:
    PaintDocument(QWidget*&);
    //    QSize minimumSizeHint() const override;
//    QSize sizeHint() const override;
    void setPresentation(Presentation* pres);
    void setCurrentPage(int);
    void setCurrentPage(QString id);
    void resizeEvent(QResizeEvent *) override;
    QSize sizeHint() const override;
    void createPDF();
    void updateFrames();
    void layoutBody();
    void layoutTitle();
    void layoutFull();
    void layoutLeft();
    void layoutRight();
    void layoutPresTitle();
    void layoutSubtitle();
signals:
    void pageNumberChanged(int page);
    void selectionChanged(std::shared_ptr<Frame>);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    int mWidth;
    void paintEvent(QPaintEvent *event) override;
    QSize mSize;
    int pageNumber;
private:
    bool move = false;
    bool scale = false;
    QPoint lastPosition;
    std::optional<BoxTransformation> momentTrafo;
    QString mActiveBoxId;
    void CursorApperance(QPoint mousePosition);
    TransformationType getTransformationType(QPoint mousePosition);
    int const diffToMouse = 25;
    QPainter painter;
    Layout mLayout;
    double mScale;
    void drawBoundingBox(QRect rect);
    void drawScaleMarker(QRect rect);
    void determineBoxInFocus(QPoint mousePos);
    QString mCurrentFrameId;
    Presentation * mPresentation;

};

#endif // PAINTDOCUMENT_H
