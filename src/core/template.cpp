#include "template.h"
#include <QFile>
#include <algorithm>

Template::Template()
{

}

void Template::readTemplateConfig(QString configFile) {
    mPresentation.loadInput(configFile);
}

BoxGeometry Template::getGeometry(QString id) const {
    auto const box = mPresentation.frameList().findBox(id);
    if(box){
        return box->geometry();
    }
    return {};
}

BoxStyle Template::getStyle(QString id) const {
    auto const box = mPresentation.frameList().findBox(id);
    if(box){
        return box->style();
    }
    return {};
}

void Template::declareVariable(QString name, QString value) {
    mVariables[name] = value;
}

void Template::setVariables(std::map<QString, QString> variables) {
    mVariables = variables;
}

Box::List Template::getTemplateSlide(QString frameId) const {
    auto frame = mPresentation.frameList().findFrame(frameId);
    if(!frame){
        return {};
    }
    auto boxes = frame->boxes();
    auto rm = [frameId](std::shared_ptr<Box> box) {return !box->id().contains(frameId + "-intern-");};
    boxes.erase(std::remove_if(boxes.begin(), boxes.end(), rm), boxes.end());
    return boxes;
}

ConfigBoxes& Template::Configuration() {
    return mPresentation.configuration();
}

void Template::setFrames(FrameList frames) {
    mPresentation.setFrames(frames);
}

FrameList Template::applyTemplate(FrameList frameList) const {
    FrameList newFrameList;
    for(auto const& frame: frameList.vector) {
        auto const frameclass = frame->frameClass();
        if(!frameclass.isEmpty()) {
            auto const boxlist = getTemplateSlide(frameclass);
            frame->setTemplateBoxes(boxlist);
        }
        for(auto const& box: frame->boxes()) {
            applyTemplateToBox(box);
        }
        newFrameList.appendFrame(frame);
    }
    return newFrameList;
}

void Template::applyTemplateToBox(Box::Ptr box) const {
    auto boxStyle = box->style();
    if(boxStyle.boxClass.isEmpty()) {
        return;
    }
    auto const boxStyleTemplate = getStyle(boxStyle.boxClass);
    if(boxStyleTemplate.empty()) {
        return;
    }
    if(!boxStyle.mAlignment) {
        boxStyle.mAlignment = boxStyleTemplate.mAlignment;
    }
    if(!boxStyle.mColor) {
        boxStyle.mColor = boxStyleTemplate.mColor;
    }
    if(!boxStyle.mFont) {
        boxStyle.mFont = boxStyleTemplate.mFont;
    }
    if(!boxStyle.mFontSize) {
        boxStyle.mFontSize = boxStyleTemplate.mFontSize;
    }
    if(!boxStyle.mFontWeight) {
        boxStyle.mFontWeight = boxStyleTemplate.mFontWeight;
    }
    if(!boxStyle.mLineSpacing) {
        boxStyle.mLineSpacing = boxStyleTemplate.mLineSpacing;
    }
    if(!boxStyle.mOpacity) {
        boxStyle.mOpacity = boxStyleTemplate.mOpacity;
    }
    if(!boxStyle.mGeometry.angle) {
        boxStyle.mGeometry.angle = boxStyleTemplate.mGeometry.angle;
    }
    if(!boxStyle.mGeometry.height) {
        boxStyle.mGeometry.height = boxStyleTemplate.mGeometry.height;
    }
    if(!boxStyle.mGeometry.left) {
        boxStyle.mGeometry.left = boxStyleTemplate.mGeometry.left;
    }
    if(!boxStyle.mGeometry.top) {
        boxStyle.mGeometry.top = boxStyleTemplate.mGeometry.top;
    }
    if(!boxStyle.mGeometry.width) {
        boxStyle.mGeometry.width = boxStyleTemplate.mGeometry.width;
    }

    box->setBoxStyle(boxStyle);
}

