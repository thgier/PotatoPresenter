/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef LATEXBOX_H
#define LATEXBOX_H

#include "box.h"

class LaTeXBox : public Box
{
public:
    LaTeXBox() = default;

    std::shared_ptr<Box> clone() override;
    void drawContent(QPainter& painter, PresentationContext const& context, PresentationRenderHints hints = PresentationRenderHints::NoRenderHints) override;
};

#endif // LATEXBOX_H
