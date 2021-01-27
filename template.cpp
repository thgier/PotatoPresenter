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
    mLayout->mBodyPos = getGeometry("Body");
    mLayout->mTitlePos = getGeometry("Title");
}

BoxGeometry Template::getGeometry(QString id) const{
    auto const box = mPresentation.getBox(id);
    if(box){
        return box->geometry();
    }
    return {};
}

BoxStyle Template::getStyle(QString id) const{
    auto const box = mPresentation.getBox(id);
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
    auto frame = mPresentation.getFrame(frameId);
    if(!frame){
        return {};
    }
    auto boxes = frame->getBoxes();
    auto rm = [frameId](std::shared_ptr<Box> box) {return !box->id().contains(frameId + "-intern-");};
    boxes.erase(std::remove_if(boxes.begin(), boxes.end(), rm), boxes.end());
    return boxes;
}

ConfigBoxes& Template::Configuration(){
    return mPresentation.Configuration();
}

void Template::setFrames(Frame::List frames){
    mPresentation.setFrames(frames);
    mLayout = std::make_shared<Layout>();
    mLayout->mBodyPos = getGeometry("Body");
    mLayout->mTitlePos = getGeometry("Title");
}

std::shared_ptr<Layout> Template::getLayout() const{
    return mLayout;
}

