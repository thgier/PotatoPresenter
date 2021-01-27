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
    void setPresentation(std::shared_ptr<Presentation> pres);
    void updateFrames();
    void setCurrentPage(int);
    void setCurrentPage(QString frameId);
    int getPageNumber() const;

    void createPDF(QString filename) const;

    void setTransformationType(TransformationType type);
    Qt::CursorShape angleToCursor(qreal angle) const;

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

    int const diffToMouse = 25;
    QPainter mPainter;
    Layout mLayout;
    double mScale;

    QPoint mCursorLastPosition;
    void cursorApperance(QPoint mousePosition);
    TransformationType getTransformationType(QPoint mousePosition);
    TransformationType mTransform = TransformationType::translate;
    std::optional<BoxTransformation> mMomentTrafo;

    void determineBoxInFocus(QPoint mousePos);
    std::vector<std::shared_ptr<Box>> determineBoxesUnderMouse(QPoint mousePos);
};

#endif // PAINTDOCUMENT_H
