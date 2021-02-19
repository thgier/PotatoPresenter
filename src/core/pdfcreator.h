#ifndef PDFCREATOR_H
#define PDFCREATOR_H

#include <QString>
#include <QPainter>

#include "presentation.h"

class PDFCreator
{
public:
    PDFCreator();
    void createPdf(QString filename, std::shared_ptr<Presentation> presentation) const;

};

#endif // PDFCREATOR_H
