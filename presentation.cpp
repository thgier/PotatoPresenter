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

void Presentation::setBox(std::shared_ptr<Box> box, QRect rect, int pageNumber){
    box->setRect(rect);
    mConfig.addRect(rect, box->id());
    emit frameChanged(pageNumber);
}
