/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "pdfcreator.h"
#include "sliderenderer.h"

#include <QPdfWriter>

PDFCreator::PDFCreator()
{
}


void PDFCreator::createPdf(QString filename, std::shared_ptr<Presentation> presentation) const{
    QPdfWriter pdfWriter(filename);
    pdfWriter.setPageSize(QPageSize(QSizeF(167.0625, 297), QPageSize::Millimeter));
    pdfWriter.setPageOrientation(QPageLayout::Landscape);
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setTitle(presentation->title());

    QPainter painter(&pdfWriter);

    painter.begin(&pdfWriter);
    painter.setWindow(QRect(QPoint(0, 0), presentation->dimensions()));
    auto paint = std::make_shared<SlideRenderer>(painter);
    paint->setRenderHints(static_cast<PresentationRenderHints>(static_cast<int>(TargetIsVectorSurface) | static_cast<int>(NoPreviewRendering)));
    for(auto &slide: presentation->slideList().vector){
        for( int i = 0; i <= slide->numberPauses(); i++) {
            paint->paintSlide(slide, i);
            if(!(slide == presentation->slideList().vector.back() && i == slide->numberPauses())){
                pdfWriter.newPage();
            }
        }
    }
    painter.end();
}

void PDFCreator::createPdfHandout(QString filename, std::shared_ptr<Presentation> presentation) const{
    QPdfWriter pdfWriter(filename);
    pdfWriter.setPageSize(QPageSize(QSizeF(167.0625, 297), QPageSize::Millimeter));
    pdfWriter.setPageOrientation(QPageLayout::Landscape);
    pdfWriter.setPageMargins(QMargins(0, 0, 0, 0));
    pdfWriter.setTitle(presentation->title());

    QPainter painter(&pdfWriter);

    painter.begin(&pdfWriter);
    painter.setWindow(QRect(QPoint(0, 0), presentation->dimensions()));
    auto paint = std::make_shared<SlideRenderer>(painter);
    for(auto &slide: presentation->slideList().vector){
        paint->paintSlide(slide);
        if(slide != presentation->slideList().vector.back()){
            pdfWriter.newPage();
        }
    }
    painter.end();
}
