#ifndef PAINTDOCUMENT_H
#define PAINTDOCUMENT_H

#include <QWidget>
#include <QSize>
#include <QPdfWriter>
#include <QPrinter>
#include <QDebug>
#include <QObject>
#include <vector>
#include <QUndoStack>
#include "frame.h"
#include "parser.h"
#include "equationcachemanager.h"
#include "presentation.h"
#include "boxgeometry.h"
#include "boxtransformation.h"
#include "snapping.h"

class FrameWidget : public QWidget
{
    Q_OBJECT
public:
    FrameWidget(QWidget*&);

    void resizeEvent(QResizeEvent *) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

    // Presentation that is shown
    void setPresentation(std::shared_ptr<Presentation> pres);
    void updateFrames();
    void updateFrameId();
    void setCurrentPage(int);
    void setCurrentPage(QString frameId);
    int pageNumber() const;
    QString const& currentFrameId() const;

    // change cursor mode: scale or rotate
    void setTransformationType(TransformationType type);

    // set the active Box on the position of a tool bar button
    void deleteBoxPosition();

    void setActiveBox(QString boxId, QString frameId);

    // trigger undo / redo actions
    void undo();
    void redo();

Q_SIGNALS:
    void selectionChanged(Frame::Ptr);
    void boxSelectionChanged(Box::Ptr);

private:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void recalculateGeometry();

    // Mouse interaction / apperance
    // scale mouse position to viewport of widget
    QPoint ScaledMousePos(QMouseEvent *event) const;
    void cursorApperance(QPoint mousePosition);
    // returns scale cursor in dependence of the angle of the rotation of the box
    Qt::CursorShape angleToCursor(qreal angle) const;

    // transform boxes
    TransformationType getTransformationType(QPoint mousePosition);
    std::vector<QString> determineVisibleBoxesUnderMouse(QPoint mousePos);
    std::vector<QString> determineBoxesUnderMouse(QPoint mousePos);
    void determineBoxInFocus(QPoint mousePos);

    // actions in Context Menu
    void createActions();
    void createAndOpenSvg();
    void openInInkscape();

private:
    std::shared_ptr<Presentation> mPresentation;
    QString mActiveBoxId;
    QString mCurrentFrameId;
    int mPageNumber = 0;

    int const mDiffToMouse = 15;

    QSize mSize;
    int mWidth;
    QFont mTitleFont;

    struct {
        // Transform from widget to frame coordinates
        QTransform mWidgetToFrameTransform;
        // Top left corner of the painted frame, in widget coordinates
        QPoint mTopLeft;
        // Frame size, in widget coordinates
        QSize mFrameSize;
    } mGeometryDetail;

    std::optional<BoxTransformation> mMomentTrafo;
    TransformationType mTransform = TransformationType::translate;
    QPoint mCursorLastPosition;

    QAction* openInkscape;
    QAction* createAndOpenInkscape;
    QAction* mUndo;
    QAction* mRedo;

    QUndoStack mUndoStack;
    ConfigBoxes mLastConfigFile;
};

#endif // PAINTDOCUMENT_H
