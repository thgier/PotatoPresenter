/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "latexbox.h"
#include "latexcachemanager.h"
#include <QSvgRenderer>

void LaTeXBox::drawContent(QPainter &painter, std::map<QString, QString> const& variables, PresentationRenderHints hints) {
    auto additionalPreamble = QString();
    // scale factor for geometry of the box
    // physical length of document: 20cm, number of pixels: 1600
    // 10pt diveded by the font size gives the scale factor
    // (Hack in the font-size because latex does not support arbitary font-sizes)
    auto const scaleFactor = 29.7 / 1600 * 10 / style().fontSize();

    auto const latexInput = "\\documentclass[10pt]{article}\\usepackage{geometry}\\usepackage[T1]{fontenc}\\geometry{paperwidth="
            + QString::number(style().paintableRect().width() * scaleFactor) + "cm, paperheight="
            + QString::number(style().paintableRect().height() * scaleFactor) +
            "cm, margin=0cm}\\pagestyle{empty}\\setlength\\parindent{0pt}\\usepackage{xcolor}\\definecolor{fontColor}{RGB}{"
            + QString::number(style().color().red()) + ", "
            + QString::number(style().color().green()) + ", "
            + QString::number(style().color().blue()) +
            "} \\usepackage{amsmath}\\usepackage{amssymb}\\usepackage{stmaryrd}\\usepackage{braket}\\renewcommand*\\familydefault{\\sfdefault}" + additionalPreamble +
            "\\begin{document}\\textcolor{fontColor}{"
            + style().text() +
            "}\\end{document}";
    QFile f("/tmp/test.tex");
    f.open(QIODevice::WriteOnly);
    f.write(latexInput.toUtf8());

    auto latex = cacheManager().getCachedImage(latexInput);
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    switch(latex.status){
    case SvgStatus::Error: {
        painter.drawText(style().paintableRect(), "Latex Error");
        return;
    }
    case SvgStatus::NotStarted:
        if(hints & PresentationRenderHints::NoPreviewRendering) {
            cacheManager().startConversionProcess(latexInput, ConversionType::BreakUntillFinished);
            latex = cacheManager().getCachedImage(latexInput);
            if(latex.status == Error) {
                return;
            }
            break;
        }
        else {
            cacheManager().startConversionProcess(latexInput);
            return;
        }
    case SvgStatus::Pending:
        return;
    case SvgStatus::Success:
        break;
    }
    latex.svg->setAspectRatioMode(Qt::KeepAspectRatio);
    latex.svg->render(&painter, style().paintableRect());
}

