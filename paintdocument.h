#ifndef PAINTDOCUMENT_H
#define PAINTDOCUMENT_H

#include <QWidget>
#include <vector>
#include <QSize>
#include <KTextEditor/Document>
#include <QMouseEvent>
#include "frame.h"
#include "parser.h"

class PaintDocument : public QWidget
{
public:
    PaintDocument();
    PaintDocument(int width);
    //    QSize minimumSizeHint() const override;
//    QSize sizeHint() const override;
    void setFrames(std::vector<std::shared_ptr<Frame>> frames);
    void updateFrames(std::vector<std::shared_ptr<Frame>> frames);
    void setCurrentPage(int);
    void resizeEvent(QResizeEvent *) override;
    std::vector<std::shared_ptr<Box>> getBoxes(std::vector<std::shared_ptr<Frame>> frames);
    std::vector<std::shared_ptr<Box>> getBoxes();
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
    QPoint lastPosition;
    std::shared_ptr<Box> movedBox;
};

#endif // PAINTDOCUMENT_H
