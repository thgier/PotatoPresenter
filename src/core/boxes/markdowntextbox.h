/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "textbox.h"
#include <QString>
#include <QSize>

class MarkdownTextBox: public TextBox
{
public:
    MarkdownTextBox(QString text, BoxStyle style, QString id, int line);
    std::shared_ptr<TextBox> clone() override;
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // TEXTFIELD_H
