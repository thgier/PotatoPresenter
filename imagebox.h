#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"
#include <QSvgRenderer>


class ImageBox: public Box
{
public:
    ImageBox(QString imagePath, BoxGeometry rect, QString id);
    void insertVariables(std::map<QString, QString> variables);
    void drawContent(QPainter& painter) override;
    int aspectRatio(QRect rect);
private:
    QString mImagePath;
    std::shared_ptr<QImage> loadImage() const;
    std::shared_ptr<QSvgRenderer> loadSvg() const;
    std::shared_ptr<QSvgRenderer> loadPdf() const;
    void drawImage(std::shared_ptr<QImage> image, QPainter& painter) const;
    void drawSvg(std::shared_ptr<QSvgRenderer> svg, QPainter& painter) const;
};

#endif // PICTURE_H
