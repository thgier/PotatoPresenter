#include "template.h"
#include <QFile>
#include <configboxes.h>
#include <algorithm>

Template::Template()
{

}

void Template::readTemplateConfig(QString configFile){
    mPresentation.loadInput(configFile);
    mLayout = std::make_shared<Layout>();
    mLayout->mBodyPos = getGeometry("body");
    mLayout->mTitlePos = getGeometry("title");
}

BoxGeometry Template::getGeometry(QString id) const{
    auto const box = mPresentation.frameList().findBox(id);
    if(box){
        return box->geometry();
    }
    return {};
}

BoxStyle Template::getStyle(QString id) const{
    auto const box = mPresentation.frameList().findBox(id);
    if(box){
        return box->style();
    }
    return {};
}

void Template::declareVariable(QString name, QString value){
    mVariables[name] = value;
}

void Template::setVariables(std::map<QString, QString> variables){
    mVariables = variables;
}

Box::List Template::getTemplateSlide(QString frameId) const{
    auto frame = mPresentation.frameList().findFrame(frameId);
    if(!frame){
        return {};
    }
    auto boxes = frame->boxes();
    auto rm = [frameId](std::shared_ptr<Box> box) {return !box->id().contains(frameId + "-intern-");};
    boxes.erase(std::remove_if(boxes.begin(), boxes.end(), rm), boxes.end());
    return boxes;
}

ConfigBoxes& Template::Configuration(){
    return mPresentation.configuration();
}

void Template::setFrames(FrameList frames){
    mPresentation.setFrames(frames);
    mLayout = std::make_shared<Layout>();
    mLayout->mBodyPos = getGeometry("body");
    mLayout->mTitlePos = getGeometry("title");
}

std::shared_ptr<Layout> Template::getLayout() const{
    return mLayout;
}

