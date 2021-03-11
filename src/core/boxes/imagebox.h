#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"
#include <QSvgRenderer>


class ImageBox: public Box
{
public:
    ImageBox(QString imagePath, BoxStyle boxstyle, QString id, int line);

    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
    bool containsPoint(QPoint point, int) const override;

    QString ImagePath() const;

private:
    std::shared_ptr<QImage> loadImage(QString path) const;
    std::shared_ptr<QSvgRenderer> loadSvg(QString path) const;
    std::shared_ptr<QSvgRenderer> loadPdf(QString path) const;
    void drawImage(std::shared_ptr<QImage> image, QPainter& painter);
    void drawSvg(std::shared_ptr<QSvgRenderer> svg, QPainter& painter);

private:
    QString mImagePath;
    QRect mBoundingBox;
};

#endif // PICTURE_H
