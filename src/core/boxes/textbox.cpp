/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "textbox.h"

TextBox::TextBox(QString text)
    : mText(text)
{
}

bool TextBox::containsPoint(QPoint point, int margin) const {
    return mTextBoundings.contains(point, margin, geometry());
}

void TextBox::appendText(QString const& text) {
    mText.append(text);
}

QString const& TextBox::text() const {
    return mText;
}
