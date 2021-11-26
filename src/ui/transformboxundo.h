/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef TRANSFORMBOXUNDO_H
#define TRANSFORMBOXUNDO_H

#include <QUndoCommand>
#include <configboxes.h>
#include <presentation.h>


class TransformBoxUndo : public QUndoCommand
{
public:
    TransformBoxUndo(std::shared_ptr<Presentation> presentation, ConfigBoxes configBefore, ConfigBoxes configAfter);
    void undo() override;
    void redo() override;

private:
    std::shared_ptr<Presentation> mPresentation;
    ConfigBoxes mConfigBefore;
    ConfigBoxes mConfigAfter;
};

#endif // TRANSFORMBOXUNDO_H
