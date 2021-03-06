/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "imagebox.h"
#include "cachemanager.h"

#include <filesystem>
#include <string>

#include <QProcess>
#include <QDebug>
#include <QTemporaryFile>
#include <QDir>

namespace  {
QRect boundingBox(QSize const& imageSize, QRect const& boxRect) {
    auto const scaledSize = imageSize.scaled(boxRect.width(), boxRect.height(), Qt::KeepAspectRatio);
    auto const x = (boxRect.width() - scaledSize.width()) / 2;
    auto const y = (boxRect.height() - scaledSize.height()) / 2;
    return QRect(QPoint(boxRect.left() + x, boxRect.top() + y), scaledSize);
};

QString absolutePath(QString &path, PresentationContext const& context) {
    if(context.mVariables.find("%{templateresourcepath}") != context.mVariables.end()) {
        return context.mVariables.at("%{templateresourcepath}") + "/" + path;
    }
    if(context.mVariables.find("%{resourcepath}") != context.mVariables.end()) {
        return context.mVariables.at("%{resourcepath}") + "/" + path;
    }
    return path;
}
}

std::shared_ptr<Box> ImageBox::clone() {
    return std::make_shared<ImageBox>(*this);
}

void ImageBox::drawContent(QPainter& painter, const PresentationContext &context, PresentationRenderHints hints){
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    auto path = substituteVariables(style().text(), context.mVariables);
    if(!QDir::isAbsolutePath(path) && context.mVariables.find("%{resourcepath}") != context.mVariables.end()) {
        path = absolutePath(path, context);
    }
    mImagePath = path;
    auto const fileInfo = QFileInfo(path);
    if(fileInfo.suffix() == "svg"){
        if(hints & PresentationRenderHints::TargetIsVectorSurface) {
            auto svg = QSvgRenderer(path);
            svg.setAspectRatioMode(Qt::KeepAspectRatio);
            svg.render(&painter, geometry().rect());
        }
        else {
            drawPixmap(loadSvg(path, geometry().size()), painter);
        }
    }
    else{
        if(hints & PresentationRenderHints::TargetIsVectorSurface) {
            auto image = QImage(path);
            painter.drawImage(boundingBox(image.size(), geometry().rect()), image);
        }
        else {
            drawPixmap(loadImage(path, geometry().size()), painter);
        }
    }
}

PixMapElement ImageBox::loadImage(QString path, QSize size) const {
    auto pixmapVector = CacheManager<PixMapVector>::instance().getData(path);
    if(pixmapVector.data && pixmapVector.data->findPixMap(size).mPixmap) {
        return pixmapVector.data->findPixMap(size);
    }
    if(pixmapVector.status == FileLoadStatus::failed){
        return {};
    }

    auto newPixmap = std::make_shared<QPixmap>(size);
    newPixmap->fill(Qt::transparent);
    QPainter painter(newPixmap.get());

    auto const image = QPixmap(path);
    auto const paintImage = image.scaled(geometry().size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    auto const source = paintImage.size();
    auto const x = (geometry().widthDisplay() - source.width()) / 2;
    auto const y = (geometry().heightDisplay() - source.height()) / 2;
    auto const boundingBox = QRect(QPoint(x, y), source);
    painter.drawPixmap({{x, y}, source}, paintImage);

    auto newPixMapVector = std::make_shared<PixMapVector>();
    if(pixmapVector.data) {
        newPixMapVector = pixmapVector.data;
    }
    newPixMapVector->insertPixmap({newPixmap, boundingBox});
    CacheManager<PixMapVector>::instance().setData(path, newPixMapVector);
    return {newPixmap, boundingBox};
}

PixMapElement ImageBox::loadSvg(QString path, QSize size) const {
    auto pixmapVector = CacheManager<PixMapVector>::instance().getData(path);
    if(pixmapVector.data && pixmapVector.data->findPixMap(size).mPixmap) {
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
    auto boundingBox = QRect({0, 0}, geometry().rect().size());
    if(geometry().height() == 0) {
        return {};
    }
    if(geometry().widthDisplay() / geometry().heightDisplay() > viewBox.width() / viewBox.height()) {
        auto const svgWidth = viewBox.width()  * geometry().heightDisplay() / (1.0 * viewBox.height());
        boundingBox.setLeft((geometry().widthDisplay() - svgWidth) / 2);
        boundingBox.setWidth(svgWidth);
    }
    else {
        auto const svgHeight = viewBox.height()  * geometry().widthDisplay() / (1.0 * viewBox.width());
        boundingBox.setTop((geometry().heightDisplay() - svgHeight) / 2);
        boundingBox.setHeight(svgHeight);
    }
    auto newPixMapVector = std::make_shared<PixMapVector>();
    if(pixmapVector.data) {
        newPixMapVector = pixmapVector.data;
    }
    newPixMapVector->insertPixmap({newPixMap, boundingBox});
    CacheManager<PixMapVector>::instance().setData(path, newPixMapVector);
    return {newPixMap, boundingBox};
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

void ImageBox::drawPixmap(PixMapElement pixmapElement, QPainter& painter) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);
    if(!pixmapElement.mPixmap){
        mBoundingBox = geometry().rect();
        return;
    }
    painter.drawPixmap(geometry().rect(), *pixmapElement.mPixmap, {{0, 0}, pixmapElement.mPixmap->size()});
    mBoundingBox = pixmapElement.mBoundingBox;
    mBoundingBox.translate(geometry().topLeft());
}

bool ImageBox::containsPoint(QPoint point, int) const {
    return mBoundingBox.contains(geometry().transform().inverted().map(point));
}

QString ImageBox::ImagePath() const{
    return mImagePath;
}
