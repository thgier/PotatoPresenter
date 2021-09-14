/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef LINEBOX_H
#define LINEBOX_H

#include "box.h"


class LineBox : public Box
{
public:
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // LINEBOX_H
