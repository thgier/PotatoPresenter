/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

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
    void createPdfHandout(QString filename, std::shared_ptr<Presentation> presentation) const;
};

#endif // PDFCREATOR_H
