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

void Template::applyTemplate(FrameList& frameList) {
    for(auto const& frame: frameList.vector) {
        auto const frameclass = frame->frameClass();
        if(!frameclass.isEmpty()) {
            auto const boxlist = getTemplateSlide(frameclass);
            frame->setTemplateBoxes(boxlist);
        }
        for(auto const& box: frame->boxes()) {
            applyTemplateToBox(box);
        }
    }
}

void Template::applyTemplateToBox(Box::Ptr box) const {
    auto boxStyle = box->style();
    if(boxStyle.boxClass.isEmpty()) {
        return;
    }
    auto boxStyleTemplate = getStyle(boxStyle.boxClass);
    if(boxStyleTemplate.empty()) {
        mPresentation.applyStandardTemplateToBox(box);
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

    boxStyle.mGeometry.setAngleIfNotSet(boxStyleTemplate.mGeometry.angle());
    boxStyle.mGeometry.setLeftIfNotSet(boxStyleTemplate.mGeometry.left());
    boxStyle.mGeometry.setTopIfNotSet(boxStyleTemplate.mGeometry.top());
    boxStyle.mGeometry.setWidthIfNotSet(boxStyleTemplate.mGeometry.width());
    boxStyle.mGeometry.setHeightIfNotSet(boxStyleTemplate.mGeometry.height());

    box->setBoxStyle(boxStyle);
}

