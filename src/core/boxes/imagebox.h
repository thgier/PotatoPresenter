#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"
#include <QSvgRenderer>


class ImageBox: public Box
{
public:
    ImageBox(QString imagePath, BoxGeometry rect, QString id);
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
    int aspectRatio(QRect rect);
    QString ImagePath() const;
private:
    QString mImagePath;
    std::shared_ptr<QImage> loadImage(QString path) const;
    std::shared_ptr<QSvgRenderer> loadSvg(QString path) const;
    std::shared_ptr<QSvgRenderer> loadPdf(QString path) const;
    void drawImage(std::shared_ptr<QImage> image, QPainter& painter) const;
    void drawSvg(std::shared_ptr<QSvgRenderer> svg, QPainter& painter) const;
};

#endif // PICTURE_H