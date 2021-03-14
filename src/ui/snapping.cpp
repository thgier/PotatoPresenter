#include "snapping.h"

Snapping::Snapping(std::vector<int> xGuides, std::vector<int> yGuides, int margin)
    : mXSnap(xGuides)
    , mYSnap(yGuides)
    , mMargin(margin)
{
}

std::optional<int> Snapping::snapX(int position) const {
    return fittingSnapObjects(position, mXSnap);
}

std::optional<int> Snapping::snapY(int position) const {
    return fittingSnapObjects(position, mYSnap);
}

std::optional<int> Snapping::fittingSnapObjects(int position, std::vector<int> possibleSnappings) const {
    std::vector<int> snappingVector;
    for(auto const possibleSnapping: possibleSnappings) {
        if(possibleSnapping - mMargin < position && possibleSnapping + mMargin > position) {
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
