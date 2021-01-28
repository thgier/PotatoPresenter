#include "imagebox.h"
#include<filesystem>
#include <string>
#include <QProcess>
#include<QDebug>
#include <QTemporaryFile>
#include "cachemanager.h"

ImageBox::ImageBox(QString imagePath, BoxGeometry rect, QString id)
    : Box(rect, id)
    , mImagePath(imagePath)
{
}

void ImageBox::insertVariables(std::map<QString, QString> variables){
    mImagePath = substituteVariables(mImagePath, variables);
}

void ImageBox::drawContent(QPainter& painter){
    auto const fileInfo = QFileInfo(mImagePath);
    if(fileInfo.suffix() == "svg"){
        drawSvg(loadSvg(), painter);
    }
    else if(fileInfo.suffix() == "pdf"){
        drawSvg(loadPdf(), painter);
    }
    else{
        drawImage(loadImage(), painter);
    }
}

std::shared_ptr<QImage> ImageBox::loadImage() const{
    auto const imageEntry = CacheManager<QImage>::instance().getData(mImagePath);
    if(imageEntry.data){
        if(imageEntry.status == FileLoadStatus::failed){
            return {};
        }
        return imageEntry.data;
    }
    auto const image = std::make_shared<QImage>(mImagePath);
    CacheManager<QImage>::instance().setData(mImagePath, image);
    return image;
}

std::shared_ptr<QSvgRenderer> ImageBox::loadSvg() const{
    auto const svgEntry = CacheManager<QSvgRenderer>::instance().getData(mImagePath);
    if(svgEntry.data && svgEntry.data->isValid()){
        return svgEntry.data;
    }
    if(svgEntry.status == FileLoadStatus::failed){
        return {};
    }
    auto const svg = std::make_shared<QSvgRenderer>(mImagePath);
    CacheManager<QSvgRenderer>::instance().setData(mImagePath, svg);
    return svg;
}

std::shared_ptr<QSvgRenderer> ImageBox::loadPdf() const{
    auto const svgEntry = CacheManager<QSvgRenderer>::instance().getData(mImagePath);
    if(svgEntry.data && svgEntry.data->isValid()){
        return svgEntry.data;
    }
    if(svgEntry.status == FileLoadStatus::failed){
        return {};
    }
    QTemporaryFile tmpFile;
    tmpFile.open();
    QString program = "/usr/bin/pdf2svg";
    QStringList arguments;
    arguments << mImagePath << tmpFile.fileName() << "1";
    QProcess *pdf2svgProcess = new QProcess();
    pdf2svgProcess->start(program, arguments);
    pdf2svgProcess->waitForFinished();
    pdf2svgProcess->deleteLater();
    auto const svg = std::make_shared<QSvgRenderer>(tmpFile.fileName());
    CacheManager<QSvgRenderer>::instance().setData(mImagePath, svg);
    return svg;
}

void ImageBox::drawImage(std::shared_ptr<QImage> image, QPainter& painter) const{
    if(!image){
        return;
    }
    startDraw(painter);
    auto const paintImage = image->scaled(geometry().rect().size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    auto const source = paintImage.size();
    auto const x = geometry().rect().left() + (geometry().rect().width() - source.width()) / 2;
    auto const y = geometry().rect().top() + (geometry().rect().height() - source.height()) / 2;
    painter.drawImage(QRect(QPoint(x, y), source), paintImage);
    endDraw(painter);
}

void ImageBox::drawSvg(std::shared_ptr<QSvgRenderer> svg, QPainter& painter) const{
    if(!svg || !svg->isValid()){
        return;
    }
    svg->setAspectRatioMode(Qt::KeepAspectRatio);
    svg->render(&painter, geometry().rect());
}
