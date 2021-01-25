#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"


class Picture: public Box
{
public:
    Picture(QString imagePath, std::map<QString, QString> variables, BoxGeometry rect, QString id);
    void drawContent(QPainter& painter) override;
    int aspectRatio(QRect rect);
private:
    QString mImagePath;
    std::shared_ptr<QImage> mImage;
};

#endif // PICTURE_H
