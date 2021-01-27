#include "imagebox.h"
#include<filesystem>
#include <string>
#include<QDebug>
#include "imagecachemanager.h"

ImageBox::ImageBox(QString imagePath, std::map<QString, QString> variables, BoxGeometry rect, QString id)
    : Box(variables, rect, id)
{
    mImagePath = substituteVariables(imagePath, mVariables);
    mImage = cacheManagerImages().getImage(mImagePath);
}

void ImageBox::drawContent(QPainter& painter){
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
