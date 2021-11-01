/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "imagebox.h"
#include<filesystem>
#include <string>
#include <QProcess>
#include<QDebug>
#include <QTemporaryFile>
#include "cachemanager.h"


void ImageBox::drawContent(QPainter& painter, std::map<QString, QString> variables){
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto path = substituteVariables(style().text(), variables);
    if(!path.startsWith("/home") && variables.find("%{resourcepath}") != variables.end()) {
        path = variables["%{resourcepath}"] + "/" + path;
    }
    auto const fileInfo = QFileInfo(path);
    if(fileInfo.suffix() == "svg"){
        auto const transform = painter.combinedTransform();
        auto const size = transform.mapRect(geometry().rect()).size();
        drawPixmap(loadSvg(path, size), painter);
    }
    else{
        drawImage(loadImage(path), painter);
    }
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

std::shared_ptr<QPixmap> ImageBox::loadSvg(QString path, QSize size) {
    auto pixmapVector = CacheManager<PixMapVector>::instance().getData(path);
    if(pixmapVector.data && pixmapVector.data->findPixMap(size)) {
        return pixmapVector.data->findPixMap(size);
    }
    if(pixmapVector.status == FileLoadStatus::failed){
        return {};
    }

    auto newPixMap = std::make_shared<QPixmap>(size);
    newPixMap->fill(Qt::transparent);
    QPainter painter(newPixMap.get());
    auto svg = QSvgRenderer(path);
    svg.setAspectRatioMode(Qt::KeepAspectRatio);
    svg.render(&painter, {{0, 0}, size});

    auto const viewBox = svg.viewBox();
    if(viewBox.isEmpty()) {
        return {};
    }
    mBoundingBox = geometry().rect();
    if(geometry().height() == 0) {
        return {};
    }
    if(geometry().width() / geometry().height() > viewBox.width() / viewBox.height()) {
        auto const svgWidth = viewBox.width()  * geometry().height() / (1.0 * viewBox.height());
        mBoundingBox.setLeft(geometry().left() + (geometry().width() - svgWidth) / 2);
        mBoundingBox.setWidth(svgWidth);
    }
    else {
        auto const svgHeight = viewBox.height()  * geometry().width() / (1.0 * viewBox.width());
        mBoundingBox.setTop(geometry().top() + (geometry().height() - svgHeight) / 2);
        mBoundingBox.setHeight(svgHeight);
    }
    auto newPixMapVector = std::make_shared<PixMapVector>();
    if(pixmapVector.data) {
        newPixMapVector = pixmapVector.data;
    }
    newPixMapVector->insertPixmap(newPixMap);
    CacheManager<PixMapVector>::instance().setData(path, newPixMapVector);
    return newPixMap;
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

void ImageBox::drawImage(std::shared_ptr<QImage> image, QPainter& painter) {
    if(!image){
        return;
    } 
    auto const paintImage = image->scaled(geometry().size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    auto const source = paintImage.size();
    auto const x = geometry().left() + (geometry().width() - source.width()) / 2;
    auto const y = geometry().top() + (geometry().height() - source.height()) / 2;
    mBoundingBox = QRect(QPoint(x, y), source);
    painter.drawImage(mBoundingBox, paintImage);
}

void ImageBox::drawPixmap(std::shared_ptr<QPixmap> pixmap, QPainter& painter) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    if(!pixmap){
        return;
    }
    painter.drawPixmap(geometry().rect(), *pixmap, {{0, 0}, pixmap->size()});
}

bool ImageBox::containsPoint(QPoint point, int) const {
    return mBoundingBox.contains(geometry().transform().inverted().map(point));
}

QString ImageBox::ImagePath() const{
    return mImagePath;
}
