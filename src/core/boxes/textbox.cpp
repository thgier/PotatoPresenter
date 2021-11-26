/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "textbox.h"


bool TextBox::containsPoint(QPoint point, int margin) const {
    return mTextBoundings.contains(point, margin, geometry());
}

void TextBox::appendText(QString const& text) {
    if(!mStyle.mText) {
        mStyle.mText = text;
        return;
    }
    mStyle.mText->append(text);
}

QString const TextBox::text() const {
    return style().text();
}
