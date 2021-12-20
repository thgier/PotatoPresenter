/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PLAINTEXTBOX_H
#define PLAINTEXTBOX_H

#include "textbox.h"

class PlainTextBox : public TextBox
{
public:
    using TextBox::TextBox;

    PlainTextBox() = default;

    std::shared_ptr<Box> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> const& variables, PresentationRenderHints hints = PresentationRenderHints::NoRenderHints) override;
};

#endif // PLAINTEXTBOX_H
