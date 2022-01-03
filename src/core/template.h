/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

# pragma once

#include <QPainter>
#include "slide.h"
#include "configboxes.h"
#include "presentationdata.h"

struct TemplateError{
    QString message;
};

class Template
{
public:
    using Ptr = std::shared_ptr<Template>;

    Template() = default;
    Template(SlideList const& slides);

    void setConfig(ConfigBoxes config);
    void setData(PresentationData data);

    // apply template to a slide list
    void applyTemplate(SlideList& slideList);

    Variables const& variables();

private:
    Box::List getTemplateSlide(QString slideId) const;

private:
    PresentationData mData;
    std::map<QString, Slide> mTemplateSlides;
    ConfigBoxes mConfig;
};
