#include "frame.h"

Frame::Frame()
    : mId{""}
{

}

Frame::Frame(const QString &id, const std::map<QString, QString> &variables, int line)
    : mId{id}
    , mVariables{variables}
    , mLine{line}
{
}

const Box::List &Frame::boxes() const
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

QString const& Frame::id() const {
    return mId;
}

Box::Ptr Frame::findBox(QString const& id) const{
    for(auto const &box: boxes()){
        if(box->id() == id){
            return box;
        }
    }
    return {};
}

bool Frame::containsBox(const QString &id) const{
    for(auto const &box: boxes()){
        if(box->id() == id){
            return true;
        }
    }
    return false;
}

void Frame::setTemplateBoxes(Box::List boxes){
    mTemplateBoxes = boxes;
}

void Frame::appendTemplateBoxes(Box::Ptr box){
    mTemplateBoxes.push_back(box);
}

Box::List Frame::templateBoxes() const{
    return mTemplateBoxes;
}

void Frame::setVariables(Variables const& variables){
    mVariables = variables;
}

Variables const& Frame::variables() const{
    return mVariables;
}

void Frame::setVariable(QString const& name, QString const& value){
    mVariables[name] = value;
}

int Frame::numberPauses() const {
    auto const& maxBox = std::max_element(mBoxes.begin(), mBoxes.end(), [](auto const& a, auto const& b){return a->pauseCounter().first < b->pauseCounter().first;});
    return maxBox->get()->pauseCounter().first + 1;
}

int Frame::line() const {
    return mLine;
}

void Frame::setFrameClass(QString const& frameClass) {
    mClass = frameClass;
}

const QString &Frame::frameClass() const {
    return mClass;
}
