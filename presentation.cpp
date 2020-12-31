#include "presentation.h"
#include <QFileInfo>
#include <QDir>
#include <QBuffer>

Presentation::Presentation() : QObject()
{
}

void Presentation::loadInput(){
    mConfig.loadConfigurationFile("/home/theresa/Documents/praes/inputConfig.json");
}

FrameList Presentation::frames(){
    return mFrames;
}

void Presentation::updateFrames(QByteArray doc){
    mParser = Parser();
    mParser.loadInput(doc, &mConfig);
    mFrames = mParser.readInput();
    emit presentationChanged();
}

bool Presentation::empty(){
    return mFrames.empty();
}

int Presentation::size(){
    return int(mFrames.size());
}

std::shared_ptr<Frame> Presentation::frameAt(int pageNumber){
    return mFrames[pageNumber];
}

void Presentation::setBox(QString boxId, BoxGeometry rect, int pageNumber){
    getBox(boxId)->setRect(rect);
    mConfig.addRect(rect, boxId);
    emit frameChanged(pageNumber);
}

std::shared_ptr<Box> Presentation::getBox(QString id) {
    if(id.isEmpty()){
        return {};
    }
    for(auto const& frame: frames()){
        for(auto const& box: frame->getBoxes()){
            if(box->id() == id) {
                return box;
            }
        }
    }
    return {};
}
