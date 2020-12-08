#include "presentation.h"
#include <QFileInfo>
#include <QDir>

Presentation::Presentation() : QObject()
{
}

void Presentation::loadInput(){
    mConfig.loadConfigurationFile("/home/theresa/Documents/praes/inputConfig.json");
}

FrameList Presentation::frames(){
    return mFrames;
}

void Presentation::updateFrames(QString doc){
    auto frames = mParser.readJson(doc, &mConfig);
    if(frames){
        mFrames = frames.value();
        emit presentationChanged();
    }
}

bool Presentation::empty(){
    return mFrames.empty();
}

int Presentation::size(){
    return int(mFrames.size());
}

std::shared_ptr<Frame> Presentation::at(int pageNumber){
    return mFrames[pageNumber];
}

void Presentation::setBox(QString boxId, QRect rect, int pageNumber){
    getBox(boxId)->setRect(rect);
    mConfig.addRect(rect, boxId);
    emit frameChanged(pageNumber);
}

std::shared_ptr<Box> Presentation::getBox(QString id) {
    for(auto const& frame: frames()){
        for(auto const& box: frame->getBoxes()){
            if(box->id() == id) {
                return box;
            }
        }
    }
    return {};
}
