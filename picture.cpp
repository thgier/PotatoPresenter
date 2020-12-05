#include "picture.h"
#include<filesystem>
#include <string>
#include<QDebug>
#include "imagecachemanager.h"

Picture::Picture(QString imagePath, QRect rect, QString id)
    : Box(rect, id)
    , mImagePath{imagePath}
//    , mImage{std::make_shared<QImage>()}
{
    mImage = cacheManagerImages().getImage(mImagePath);
}

void Picture::drawContent(QPainter& painter){
//    Box::drawContent(painter);
    if(!mImage){
        return;
    }
    auto const paintImage = mImage->scaled(Rect().size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    auto const source = paintImage.size();
    auto const x = Rect().left() + (Rect().width() - source.width()) / 2;
    auto const y = Rect().top() + (Rect().height() - source.height()) / 2;
    painter.drawImage(QRect(QPoint(x, y), source), paintImage);
}
