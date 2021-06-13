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

ImageBox::ImageBox(QString imagePath, BoxStyle boxstyle, QString id, int line)
    : Box(boxstyle, id, line)
    , mImagePath(imagePath)
{
}

void ImageBox::drawContent(QPainter& painter, std::map<QString, QString> variables){
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto path = substituteVariables(mImagePath, variables);
    if(!path.startsWith("/home") && variables.find("%{resourcepath}") != variables.end()) {
        path = variables["%{resourcepath}"] + "/" + path;
    }
    auto const fileInfo = QFileInfo(path);
    if(fileInfo.suffix() == "svg"){
        drawSvg(loadSvg(path), painter);
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

void ImageBox::drawSvg(std::shared_ptr<QSvgRenderer> svg, QPainter& painter) {
    if(!svg || !svg->isValid()){
        return;
    }
    svg->setAspectRatioMode(Qt::KeepAspectRatio);
    svg->render(&painter, geometry().rect());

    auto const viewBox = svg->viewBox();
    mBoundingBox = geometry().rect();
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
}

bool ImageBox::containsPoint(QPoint point, int) const {
    return mBoundingBox.contains(geometry().transform().inverted().map(point));
}

QString ImageBox::ImagePath() const{
    return mImagePath;
}
