#include "frame.h"

Frame::Frame()
    : mId{""}
{

}

Frame::Frame(QString id)
    : mId{id}
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
