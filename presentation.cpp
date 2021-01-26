#include "presentation.h"
#include <QFileInfo>
#include <QDir>
#include <QBuffer>

Presentation::Presentation() : QObject()
{
}

void Presentation::loadInput(QString configFilename){
    mConfig.loadConfigurationFile(configFilename);
}

FrameList Presentation::frames() const{
    return mFrames;
}

void Presentation::setFrames(Frame::List frames){
    mFrames = frames;
    emit presentationChanged();
}

bool Presentation::empty() const{
    return mFrames.empty();
}

int Presentation::size() const{
    return int(mFrames.size());
}

std::shared_ptr<Frame> Presentation::frameAt(int pageNumber) const{
    return mFrames[pageNumber];
}

void Presentation::setBox(QString boxId, BoxGeometry rect, int pageNumber){
    getBox(boxId)->setRect(rect);
    mConfig.addRect(rect, boxId);
    emit frameChanged(pageNumber);
}

std::shared_ptr<Box> Presentation::getBox(QString id) const {
    for(auto const& frame: frames()){
        for(auto const& box: frame->getBoxes()){
            if(box->id() == id) {
                return box;
            }
        }
    }
    return {};
}

std::shared_ptr<Frame> Presentation::getFrame(QString id) const{
    for(auto const &frame: frames()){
        if(id == frame->id()){
            return frame;
        }
    }
    return {};
}

void Presentation::saveConfig(QString file){
    mConfig.saveConfig(file);
}

ConfigBoxes& Presentation::Configuration(){
    return mConfig;
}
