#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"


class Picture: public Box
{
public:
    Picture(QString imagePath, QRect rect, int id);
    void drawContent(QPainter& painter) override;
    int aspectRatio(QRect rect);
private:
    QString mImagePath;
    QImage mImage;
};

#endif // PICTURE_H
