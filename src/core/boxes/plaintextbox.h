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

    std::shared_ptr<TextBox> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // PLAINTEXTBOX_H
