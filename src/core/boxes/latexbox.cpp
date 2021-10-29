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
    auto const latexInput = "\\documentclass[10pt]{article}\\usepackage{geometry}\\usepackage[T1]{fontenc}\\geometry{paperwidth="
            + QString::number(20. * geometry().width() / 1600. / style().fontSize() * 10) + "cm, paperheight="
            + QString::number(20. * geometry().height() / 1600. / style().fontSize() * 10) +
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

