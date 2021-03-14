#ifndef SNAPPING_H
#define SNAPPING_H

#include "box.h"

class Snapping
{
public:
    Snapping() = default;
    Snapping(std::vector<int> xGuides, std::vector<int> yGuides, int margin);

    std::optional<int> snapX(int position) const;
    std::optional<int> snapY(int position) const;

    void setMargin(int margin);

private:
    std::optional<int> fittingSnapObjects(int position, std::vector<int> possibleSnappings) const;

private:
    std::vector<int> mXSnap;
    std::vector<int> mYSnap;
    int mMargin = 25;
};

#endif // SNAPPING_H
