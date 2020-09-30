#ifndef PAINTDOCUMENT_H
#define PAINTDOCUMENT_H

#include <QWidget>
#include <vector>
#include <QSize>
#include <KTextEditor/Document>
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
    void setCurrentPage(int);
    void resizeEvent(QResizeEvent *) override;
protected:
    double aspectRatio;
    int mWidth;
    void paintEvent(QPaintEvent *event) override;
    std::vector<std::shared_ptr<Frame>> mFrames;
    QSize mSize;
    int pageNumber;
};

#endif // PAINTDOCUMENT_H
