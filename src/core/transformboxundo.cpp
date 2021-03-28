/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "transformboxundo.h"

TransformBoxUndo::TransformBoxUndo(std::shared_ptr<Presentation> presentation, ConfigBoxes configBefore, ConfigBoxes configAfter)
    : mPresentation(presentation)
    , mConfigBefore(configBefore)
    , mConfigAfter(configAfter)
{
}

void TransformBoxUndo::undo() {
    mPresentation->setConfig(mConfigBefore);
}

void TransformBoxUndo::redo() {
    mPresentation->setConfig(mConfigAfter);
}
