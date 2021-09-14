/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef CODEBOX_H
#define CODEBOX_H

#include "textbox.h"

class CodeBox : public TextBox
{
public:
    CodeBox(QString text);

    std::shared_ptr<TextBox> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // CODEBOX_H
