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

void ImageBox::drawContent(QPainter& painter, std::map<QString, QString> variables){
    auto const path = substituteVariables(mImagePath, variables);
    auto const fileInfo = QFileInfo(path);
    startDraw(painter);
    if(fileInfo.suffix() == "svg"){
        drawSvg(loadSvg(path), painter);
    }
    else if(fileInfo.suffix() == "pdf"){
        drawSvg(loadPdf(path), painter);
    }
    else{
        drawImage(loadImage(path), painter);
    }
    endDraw(painter);
}

std::shared_ptr<QImage> ImageBox::loadImage(QString path) const{
    auto const imageEntry = CacheManager<QImage>::instance().getData(path);
    if(imageEntry.data){
        if(imageEntry.status == FileLoadStatus::failed){
            return {};
        }
        return imageEntry.data;
    }
    auto const image = std::make_shared<QImage>(path);
    CacheManager<QImage>::instance().setData(path, image);
    return image;
}

std::shared_ptr<QSvgRenderer> ImageBox::loadSvg(QString path) const{
    auto const svgEntry = CacheManager<QSvgRenderer>::instance().getData(path);
    if(svgEntry.data && svgEntry.data->isValid()){
        return svgEntry.data;
    }
    if(svgEntry.status == FileLoadStatus::failed){
        return {};
    }
    auto const svg = std::make_shared<QSvgRenderer>(path);
    CacheManager<QSvgRenderer>::instance().setData(path, svg);
    return svg;
}

std::shared_ptr<QSvgRenderer> ImageBox::loadPdf(QString path) const{
    auto const svgEntry = CacheManager<QSvgRenderer>::instance().getData(path);
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
    arguments << path << tmpFile.fileName() << "1";
    QProcess *pdf2svgProcess = new QProcess();
    pdf2svgProcess->start(program, arguments);
    pdf2svgProcess->waitForFinished();
    pdf2svgProcess->deleteLater();
    auto const svg = std::make_shared<QSvgRenderer>(tmpFile.fileName());
    CacheManager<QSvgRenderer>::instance().setData(path, svg);
    return svg;
}

void ImageBox::drawImage(std::shared_ptr<QImage> image, QPainter& painter) const{
    if(!image){
        return;
    } 
    auto const paintImage = image->scaled(geometry().rect().size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    auto const source = paintImage.size();
    auto const x = geometry().rect().left() + (geometry().rect().width() - source.width()) / 2;
    auto const y = geometry().rect().top() + (geometry().rect().height() - source.height()) / 2;
    painter.drawImage(QRect(QPoint(x, y), source), paintImage);
}

void ImageBox::drawSvg(std::shared_ptr<QSvgRenderer> svg, QPainter& painter) const{
    if(!svg || !svg->isValid()){
        return;
    }
    svg->setAspectRatioMode(Qt::KeepAspectRatio);
    svg->render(&painter, geometry().rect());
}
