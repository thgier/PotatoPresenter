#include "latexbox.h"
#include "latexcachemanager.h"
#include <QSvgRenderer>

LaTeXBox::LaTeXBox(QString text)
{
//    text.replace("\n", " ");
    mText = text;
//    mLatexInput = "\\documentclass{standalone}\\usepackage{"
//            + style().font() +
//            "}\\usepackage[T1]{fontenc}\\usepackage[dvipsnames]{xcolor}\\definecolor{myColor}{RGB}{"
//            + style().color().red() + ","
//            + style().color().green() + ","
//            + style().color().blue() + "}\\usepackage{transparent}\\usepackage{tikz}\\usepackage[]{siunitx}\\usepackage{mathabx}\\usepackage{braket}\\begin{document}\\color{myColor}\\transparent{"
//            + style().opacity() + "}"
//            + text +
//            "\\end{document}";
}

void LaTeXBox::drawContent(QPainter &painter, std::map<QString, QString> variables) {
    auto additionalPreamble = QString();
    auto  font = style().font();
    if(font == "DejaVu Sans") {
        font = "DejaVuSans";
        additionalPreamble += "\\renewcommand*\\familydefault{\\sfdefault}";
    }
    // scale factor for geometry of the box
    // physical length of document: 20cm, number of pixels: 1600
    // 10pt diveded by the font size gives the scale factor
    // (Hack in the font-size because latex does not support arbitary font-sizes)
    auto const scaleFactor = 29.7 / 1600 * 10 / style().fontSize();

    auto const latexInput = "\\documentclass[10pt]{article}\\usepackage{geometry}\\usepackage[T1]{fontenc}\\geometry{paperwidth="
            + QString::number(geometry().width() * scaleFactor) + "cm, paperheight="
            + QString::number(geometry().height() * scaleFactor) +
            "cm, margin=0cm}\\pagestyle{empty}\\setlength\\parindent{0pt}\\usepackage{xcolor}\\definecolor{fontColor}{RGB}{"
            + QString::number(style().color().red()) + ", "
            + QString::number(style().color().green()) + ", "
            + QString::number(style().color().blue()) +
            "}\\usepackage{"
            + font +
            "}" + additionalPreamble +
            "\\begin{document}\\textcolor{fontColor}{"
            + mText +
            "}\\end{document}";
    QFile f("/tmp/test.tex");
    f.open(QIODevice::WriteOnly);
    f.write(latexInput.toUtf8());

    auto const latex = cacheManager().getCachedImage(latexInput);
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    switch(latex.status){
    case SvgStatus::Error: {
        painter.drawText(geometry().rect(), "Latex Error");
        return;
    }
    case SvgStatus::NotStarted:
        cacheManager().startConversionProcess(latexInput);
        return;
    case SvgStatus::Pending:
        return;;
    case SvgStatus::Success:
        break;
    }
    latex.svg->setAspectRatioMode(Qt::KeepAspectRatio);
    latex.svg->render(&painter, geometry().rect());
}

