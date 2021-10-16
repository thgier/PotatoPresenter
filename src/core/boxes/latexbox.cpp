#include "latexbox.h"

LaTeXBox::LaTeXBox(QString text)
{
    QString const latexInput = "\\documentclass{standalone}\n\\usepackage{"
            + style().font() +
            "}\n\\usepackage[T1]{fontenc}\n\\usepackage[dvipsnames]{xcolor}\n\\definecolor{myColor}{RGB}{"
            + style().color().red() + ","
            + style().color().green() + ","
            + style().color().blue() + "}\n \\usepackage{transparent}\n\\usepackage{tikz}\n\\usepackage[]{siunitx}\\usepackage{mathabx}\\usepackage{braket}\n\\begin{document}\\color{myColor}\\transparent{style().opacity()}"
            + text +
            "\\end{document}";

}
