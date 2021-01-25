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
    //    QSize minimumSizeHint() const override;
//    QSize sizeHint() const override;
    void setPresentation(std::shared_ptr<Presentation> pres);
    void setCurrentPage(int);
    void setCurrentPage(QString id);
    void resizeEvent(QResizeEvent *) override;
    QSize sizeHint() const override;
    void createPDF(QString filename);
    void updateFrames();
    void layoutBody();
    void layoutTitle();
    void layoutFull();
    void layoutLeft();
    void layoutRight();
    void layoutPresTitle();
    void layoutSubtitle();
    void setTransformationType(TransformationType type);
    Qt::CursorShape angleToCursor(qreal angle);
    int getPageNumber() const;
signals:
    void pageNumberChanged(int page);
    void selectionChanged(std::shared_ptr<Frame>);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
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
    void cursorApperance(QPoint mousePosition);
    TransformationType getTransformationType(QPoint mousePosition);
    int const diffToMouse = 25;
    QPainter painter;
    Layout mLayout;
    double mScale;
    void determineBoxInFocus(QPoint mousePos);
    std::vector<std::shared_ptr<Box>> determineBoxesUnderMouse(QPoint mousePos);
    QString mCurrentFrameId;
    std::shared_ptr<Presentation> mPresentation;
    TransformationType mTransform = TransformationType::translate;

};

#endif // PAINTDOCUMENT_H
