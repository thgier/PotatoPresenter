#include "frame.h"

Frame::Frame()
    : mId{""}
{

}

Frame::Frame(QString id, std::map<QString, QString> variables)
    : mId{id}
    , mVariables{variables}
{
}

std::vector<std::shared_ptr<Box>> Frame::getBoxes() const
{
    return mBoxes;
}

void Frame::appendBox(std::shared_ptr<Box> box)
{
    mBoxes.push_back(box);
}

void Frame::setBoxes(std::vector<std::shared_ptr<Box>> boxes){
    mBoxes = boxes;
}

bool Frame::empty() {
    return mBoxes.empty();
}

QString Frame::id() {
    return mId;
}

std::shared_ptr<Box> Frame::getBox(QString id) const{
    for(auto const &box: getBoxes()){
        if(box->id() == id){
            return box;
        }
    }
    return {};
}

bool Frame::containsBox(QString id) const{
    for(auto const &box: getBoxes()){
        if(box->id() == id){
            return true;
        }
    }
    return false;
}

void Frame::setTemplateBoxes(Box::List boxes){
    mTemplateBoxes = boxes;
}

void Frame::appendTemplateBoxes(std::shared_ptr<Box> box){
    mTemplateBoxes.push_back(box);
}

Box::List Frame::getTemplateBoxes() const{
    return mTemplateBoxes;
}

void Frame::setVariables(std::map<QString, QString> variables){
    mVariables = variables;
}

std::map<QString, QString> Frame::Variables() const{
    return mVariables;
}

void Frame::setVariable(QString name, QString value){
    mVariables[name] = value;
}