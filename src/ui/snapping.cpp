#include "snapping.h"

Snapping::Snapping(std::vector<int> xGuides, std::vector<int> yGuides)
{
    mXSnap = xGuides;
    mYSnap = yGuides;
}

std::optional<int> Snapping::snapX(int position, int margin) const {
    return fittingSnapObjects(position, mXSnap, margin);
}

std::optional<int> Snapping::snapY(int position, int margin) const {
    return fittingSnapObjects(position, mYSnap, margin);
}

std::optional<int> Snapping::fittingSnapObjects(int position, std::vector<int> possibleSnappings, int margin) const {
    std::vector<int> snappingVector;
    for(auto const possibleSnapping: possibleSnappings) {
        if(possibleSnapping - margin < position && possibleSnapping + margin > position) {
            snappingVector.push_back(possibleSnapping);
        }
    }
    if(snappingVector.empty()) {
        return {};
    }
    auto const compare = [position](auto a, auto b){
        return std::abs(a - position) < std::abs(b - position);
    };
    return *std::min_element(snappingVector.begin(), snappingVector.end(), compare);
}
