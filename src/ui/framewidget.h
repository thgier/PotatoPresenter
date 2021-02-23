#ifndef PAINTDOCUMENT_H
#define PAINTDOCUMENT_H

#include <QWidget>
#include <QSize>
#include <QPdfWriter>
#include <QPrinter>
#include <QDebug>
#include <QObject>
#include <vector>
#include "frame.h"
#include "parser.h"
#include "layout.h"
#include "equationcachemanager.h"
#include "presentation.h"
#include "boxgeometry.h"
#include "boxtransformation.h"

class FrameWidget : public QWidget
{
    Q_OBJECT
public:
    FrameWidget(QWidget*&);

    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

//    Presentation that is shown
    void setPresentation(std::shared_ptr<Presentation> pres);
    void updateFrames();
    void setCurrentPage(int);
    void setCurrentPage(QString frameId);
    int pageNumber() const;

//    change cursor mode: scale or rotate
    void setTransformationType(TransformationType type);

//    set the active Box on the position of a tool bar button
    void layoutBody();
    void layoutTitle();
    void layoutFull();
    void layoutLeft();
    void layoutRight();
    void layoutPresTitle();
    void layoutSubtitle();
    void deleteBoxPosition();

Q_SIGNALS:
    void pageNumberChanged(int page);
    void selectionChanged(Frame::Ptr);

private:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

//    Mouse interaction / apperance
//    scale mouse position to viewport of widget
    QPoint ScaledMousePos(QMouseEvent *event) const;
    void cursorApperance(QPoint mousePosition);
//    returns scale cursor in dependence of the angle of the rotation of the box
    Qt::CursorShape angleToCursor(qreal angle) const;

//    transform boxes
    TransformationType getTransformationType(QPoint mousePosition);
    Box::List determineBoxesUnderMouse(QPoint mousePos);
    void determineBoxInFocus(QPoint mousePos);

//    actions in Context Menu
    void createActions();
    void createAndOpenSvg();
    void openInInkscape();

private:
    std::shared_ptr<Presentation> mPresentation;
    QString mActiveBoxId;
    QString mCurrentFrameId;
    int mPageNumber;

    int const mDiffToMouse = 15;
    QPainter mPainter;
    Layout mLayout;

    double mScale;
    QSize mSize;
    int mWidth;

    std::optional<BoxTransformation> mMomentTrafo;
    TransformationType mTransform = TransformationType::translate;
    QPoint mCursorLastPosition;

    QAction* openInkscape;
    QAction* createAndOpenInkscape;
};

#endif // PAINTDOCUMENT_H
