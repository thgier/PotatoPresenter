#ifndef SNAPPING_H
#define SNAPPING_H

#include "box.h"

class Snapping
{
public:
    Snapping() = default;
    Snapping(std::vector<int> xGuides, std::vector<int> yGuides);
    std::optional<int> snapX(int position, int margin) const;
    std::optional<int> snapY(int position, int margin) const;

private:
    std::optional<int> fittingSnapObjects(int position, std::vector<int> possibleSnappings, int margin) const;

private:
    std::vector<int> mXSnap;
    std::vector<int> mYSnap;
};

#endif // SNAPPING_H
