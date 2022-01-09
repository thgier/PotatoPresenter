#ifndef TABLEOFCONTENTSBOX_H
#define TABLEOFCONTENTSBOX_H

#include "textbox.h"

class TableofContentsBox : public TextBox
{
public:
    TableofContentsBox() = default;

    std::shared_ptr<Box> clone() override;
    void drawContent(QPainter& painter, const PresentationContext &context, PresentationRenderHints hints) override;

private:
    void drawEntry(QPainter &painter, QPointF& startOfLine, QString const& section);
    void drawItemMarker(QPainter &painter, QPointF & startofLine);
};

#endif // TABLEOFCONTENTSBOX_H
