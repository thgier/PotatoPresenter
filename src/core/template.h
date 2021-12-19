/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

# pragma once

#include <QPainter>
#include "slide.h"
#include "configboxes.h"
#include "presentation.h"

struct TemplateError{
    QString message;
};

class Template
{
public:
    using Ptr = std::shared_ptr<Template>;
    using variablesMap = std::shared_ptr<std::map<QString, QString>>;

    Template();
    Template(SlideList slides);

    // set data
    void setSlides(SlideList slides);
    void setConfig(ConfigBoxes config);

    // apply template to a slide list
    void applyTemplate(SlideList& slideList);

    Variables const& variables();

private:
    Box::List getTemplateSlide(QString slideId) const;

private:
    Presentation mPresentation;
    std::map<QString, Slide> mTemplateSlides;
    Variables mVariables;
};
