#pragma once

#include <string>
#include <vector>
#include <QVariant>
#include "box.h"

class Frame
{
public:
    using ptr = std::shared_ptr<Frame>;
    Frame();
    Frame(QString id);
    std::vector<std::shared_ptr<Box>> getBoxes() const;
    void appendBox(std::shared_ptr<Box> box);
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);
    bool empty();
    QString id();

private:
    std::vector<std::shared_ptr<Box>> mBoxes;
    QString mId;
};

Q_DECLARE_METATYPE(std::shared_ptr<Frame>)
