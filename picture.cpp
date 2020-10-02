#include "picture.h"
#include<filesystem>
#include <string>
#include<QDebug>

Picture::Picture(QString imagePath, QRect rect)
    : Box(rect)
    , mImagePath{imagePath}
    , mImage(QImage())
{
    if(std::filesystem::exists(imagePath.toStdString())){
        mImage.load(mImagePath);
    }

}

void Picture::drawContent(QPainter& painter){
    if(mImage.isNull()){
        return;
    }
    auto const paintImage = mImage.scaled(Rect().size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    auto const source = paintImage.size();
    auto const x = Rect().left() + (Rect().width() - source.width()) / 2;
    auto const y = Rect().top() + (Rect().height() - source.height()) / 2;
    painter.drawImage(QRect(QPoint(x, y), source), paintImage);
}
