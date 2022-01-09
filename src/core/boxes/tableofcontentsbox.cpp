#include "tableofcontentsbox.h"
#include <QTextLayout>

namespace {

QString findVariable(PresentationContext const& context, QString const& variable) {
    if(auto const value = context.mVariables.find(variable); value != context.mVariables.end()){
        return value->second;
    }
    return {};
}
}

std::shared_ptr<Box> TableofContentsBox::clone() {
    return std::make_shared<TableofContentsBox>(*this);
}

void TableofContentsBox::drawContent(QPainter& painter, const PresentationContext &context, PresentationRenderHints hints) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    auto startLine = QPointF(0, 0);
    auto const linespacing = painter.fontMetrics().leading() + mStyle.linespacing() * painter.fontMetrics().lineSpacing();

    auto const tableofcontents = context.mTableOfContent;
    auto const currentSection = findVariable(context, "%{section}");
    auto const currentSubsection = findVariable(context, "%{subsection}");

    auto highlightcurrentSection = style().highlight();
    if(currentSection.isEmpty()) {
        highlightcurrentSection = false;
    }

    for(auto const& section: tableofcontents.sections) {
        if(currentSection == section.name || !highlightcurrentSection) {
            painter.setOpacity(1);
        }
        else {
            painter.setOpacity(0.5);
        }
        painter.save();
        painter.setBrush(style().color());
        startLine.setX(painter.fontMetrics().xHeight() * 3.0);
        drawItemMarker(painter, startLine);
        painter.restore();

        drawEntry(painter, startLine, section.name);

        for(auto const& subsection: section.subsection) {
            startLine.setX(painter.fontMetrics().xHeight() * 6.0);
            if(currentSubsection == subsection.name && currentSection == section.name || !highlightcurrentSection) {
                painter.setOpacity(1);
            }
            else {
                painter.setOpacity(0.5);
            }
            drawItemMarker(painter, startLine);
            drawEntry(painter, startLine, subsection.name);
        }
        startLine += {0, linespacing * 0.25};
    }
}

void TableofContentsBox::drawEntry(QPainter& painter, QPointF &startOfLine, const QString &section) {
    auto const linespacing = painter.fontMetrics().leading() + style().linespacing() * painter.fontMetrics().lineSpacing();
    QTextLayout textLayout(section);
    textLayout.setFont(painter.font());
    textLayout.setCacheEnabled(true);
    textLayout.beginLayout();
    while (1) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid()){
            break;
        }
        line.setLineWidth(style().paintableRect().width());
        line.setPosition(startOfLine);
        mTextBoundings.lineBoundingRects.push_back(line.naturalTextRect());
        startOfLine += {0, linespacing};
    }
    textLayout.endLayout();
    textLayout.draw(&painter, style().paintableRect().topLeft());
}

void TableofContentsBox::drawItemMarker(QPainter &painter, QPointF & startofLine) {
    auto const markerSize = painter.fontMetrics().xHeight() * 0.25;
    auto middleItem = startofLine;
    middleItem += {0,  painter.fontMetrics().height() * 0.5};
    startofLine += {markerSize + painter.fontMetrics().horizontalAdvance("  "), 0};
    painter.drawEllipse(middleItem + style().paintableRect().topLeft(), markerSize, markerSize);
}


