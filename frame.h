#ifndef FRAME_H
#define FRAME_H

#include <string>
#include <vector>
#include "box.h"

typedef std::basic_string<char> string;

class Frame
{
public:
    using ptr = std::shared_ptr<Frame>;
    Frame();
    std::vector<std::shared_ptr<Box>> getBoxes();
    void appendBox(std::shared_ptr<Box> box);
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);

private:
    string title;
    int pageNumber;
    string text;
    std::vector<std::shared_ptr<Box>> mBoxes;
};

#endif // FRAME_H
