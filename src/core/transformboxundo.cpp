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
