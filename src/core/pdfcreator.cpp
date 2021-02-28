#include "pdfcreator.h"
#include "framepainter.h"

#include <QPdfWriter>

PDFCreator::PDFCreator()
{
}


void PDFCreator::createPdf(QString filename, std::shared_ptr<Presentation> presentation) const{
    QPdfWriter pdfWriter(filename);
    auto const pdfLayout = QPageLayout(QPageSize(QSize(160, 90)), QPageLayout::Portrait, QMarginsF(0, 0, 0, 0), QPageLayout::Millimeter);
    pdfWriter.setPageLayout(pdfLayout);

    QPainter painter(&pdfWriter);
    painter.setWindow(QRect(QPoint(0, 0), presentation->dimensions()));

    painter.begin(&pdfWriter);
    auto paint = std::make_shared<FramePainter>(painter);
    for(auto &frame: presentation->frameList().vector){
        for( int i = 0; i < frame->numberPauses(); i++) {
            paint->paintFrame(frame, i);
            if(!(frame == presentation->frameList().vector.back() && i == frame->numberPauses() - 1)){
                pdfWriter.newPage();
            }
        }
    }
    painter.end();
}
