/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once
#include "box.h"

BoxStyle propertyMapToBoxStyle(Box::Properties const& properties);
BoxStyle variablesToBoxStyle(Variables const& variables);

void applyProperty(QString const& property, QString const& value, int line, BoxStyle & boxstyle);
void applyProperty(QString const& property, PropertyEntry const& entry, BoxStyle & boxstyle);

Box::List copy(Box::List const& input);
