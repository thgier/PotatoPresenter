#include "picture.h"
#include<filesystem>
#include <string>
#include<QDebug>
#include "imagecachemanager.h"

Picture::Picture(QString imagePath, BoxGeometry rect, QString id)
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
    startDraw(painter);
    auto const paintImage = mImage->scaled(geometry().rect().size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    auto const source = paintImage.size();
    auto const x = geometry().rect().left() + (geometry().rect().width() - source.width()) / 2;
    auto const y = geometry().rect().top() + (geometry().rect().height() - source.height()) / 2;
    painter.drawImage(QRect(QPoint(x, y), source), paintImage);
    endDraw(painter);
}
