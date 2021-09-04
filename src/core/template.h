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
    void setSlides(SlideList slides);
    void readTemplateConfig(QString configFile);
    void applyTemplate(SlideList& slideList);
    BoxGeometry getGeometry(QString id) const;
    BoxStyle getStyle(QString id) const;
    void declareVariable(QString name, QString value);
    void drawTemplate(QString slideId);
    Box::List getTemplateSlide(QString slideId) const;
    void setVariables(std::map<QString, QString> variables);
    ConfigBoxes& Configuration();

private:
    void applyTemplateToBox(Box::Ptr box) const;

private:
    Presentation mPresentation;
    std::map<QString, QString> mVariables;
    std::map<QString, Slide> mTemplateSlides;
};
