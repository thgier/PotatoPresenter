#include "sectionpreviewbox.h"

namespace  {
void drawPoints(QPainter &painter, QPointF position, int diameter, int number, int marked=-1) {
    position += {0.5 * diameter, 0};
    for (int i = 0; i < number; i++) {
        painter.setBrush({});
        if(marked == i) {
            painter.setBrush(painter.pen().color());
        }
        painter.drawEllipse(QRectF(position, QSize(diameter, diameter)));
        position += {1.5 * diameter, 0};
    }
}
}

std::shared_ptr<Box> SectionPreviewBox::clone() {
    return std::make_shared<SectionPreviewBox>(*this);
}

void SectionPreviewBox::drawContent(QPainter &painter, const PresentationContext &context, PresentationRenderHints hints) {
    PainterTransformScope scope(this, painter);
    drawGlobalBoxSettings(painter);

    auto startText = style().paintableRect().topLeft() + QPoint(0, painter.fontMetrics().height());
    auto const startOpacity = painter.opacity();
    auto const opacity = 0.3 * startOpacity;

    for(auto const& section: context.mTableOfContent.sections) {
        painter.setOpacity(opacity);
        bool currentSection = false;
        if(context.mPagenumber >= section.startPage && context.mPagenumber < section.startPage + section.length) {
            painter.setOpacity(startOpacity);
            currentSection = true;
        }
        painter.drawText(startText, section.name);

        auto startPoints = startText + QPointF(0, 0.5 * painter.fontMetrics().lineSpacing());
        auto const diameterPoints = 0.7 * painter.fontMetrics().xHeight();

        if(section.subsection.empty()) {
            int markedItem = -1;
            painter.setOpacity(opacity);
            if(currentSection) {
                markedItem = context.mPagenumber - section.startPage;
                painter.setOpacity(startOpacity);
            }
            drawPoints(painter, startPoints, diameterPoints, section.length, markedItem);
        }

        for(auto const& subsection: section.subsection) {
            int markedItem = -1;
            painter.setOpacity(opacity);
            if(currentSection &&
                    context.mPagenumber >= subsection.startPage && context.mPagenumber < subsection.startPage + subsection.length) {
                markedItem = context.mPagenumber - section.startPage;
                painter.setOpacity(startOpacity);
            }
            drawPoints(painter, startPoints, diameterPoints, section.length, markedItem);
            startPoints += {0, 1.7 * diameterPoints};
        }

        startText += {painter.fontMetrics().horizontalAdvance(section.name) +
                20 * painter.fontMetrics().horizontalAdvance(" "), 0};
    }
}
