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

class PaintDocument : public QWidget
{
    Q_OBJECT
public:
    PaintDocument(QWidget*&);
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void setPresentation(std::shared_ptr<Presentation> pres);
    void updateFrames();
    void setCurrentPage(int);
    void setCurrentPage(QString frameId);
    int getPageNumber() const;

    void setTransformationType(TransformationType type);
    Qt::CursorShape angleToCursor(qreal angle) const;

    void layoutBody();
    void layoutTitle();
    void layoutFull();
    void layoutLeft();
    void layoutRight();
    void layoutPresTitle();
    void layoutSubtitle();

Q_SIGNALS:
    void pageNumberChanged(int page);
    void selectionChanged(std::shared_ptr<Frame>);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    QSize mSize;
    int mWidth;
    int pageNumber;

private:
    std::shared_ptr<Presentation> mPresentation;
    QString mActiveBoxId;
    QString mCurrentFrameId;

    int const diffToMouse = 15;
    QPainter mPainter;
    Layout mLayout;
    double mScale;

    QPoint mCursorLastPosition;
    QPoint ScaledMousePos(QMouseEvent *event) const;
    void cursorApperance(QPoint mousePosition);
    TransformationType getTransformationType(QPoint mousePosition);
    TransformationType mTransform = TransformationType::translate;
    std::optional<BoxTransformation> mMomentTrafo;

    void determineBoxInFocus(QPoint mousePos);
    std::vector<std::shared_ptr<Box>> determineBoxesUnderMouse(QPoint mousePos);

    void createActions();
    void createAndOpenSvg();
    void openInInkscape();
    QAction* openInkscape;
    QAction* createAndOpenInkscape;
};

#endif // PAINTDOCUMENT_H
