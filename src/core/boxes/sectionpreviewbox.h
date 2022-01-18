#ifndef SECTIONPREVIEWBOX_H
#define SECTIONPREVIEWBOX_H

#include "textbox.h"

class SectionPreviewBox : public TextBox
{
public:
    SectionPreviewBox() = default;

    std::shared_ptr<Box> clone() override;

    void drawContent(QPainter& painter, PresentationContext const& context, PresentationRenderHints hints = PresentationRenderHints::NoRenderHints) override;
};

#endif // SECTIONPREVIEWBOX_H
