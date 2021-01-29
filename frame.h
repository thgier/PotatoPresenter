#pragma once

#include <string>
#include <vector>
#include <QVariant>
#include "box.h"

class Frame
{
public:
    using List = std::vector<std::shared_ptr<Frame>>;
    using ptr = std::shared_ptr<Frame>;
    Frame();
    Frame(QString id, int pageNumber);
    Box::List getBoxes() const;
    std::shared_ptr<Box> getBox(QString id) const;
    bool IdExists(QString id) const;
    void appendBox(std::shared_ptr<Box> box);
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);
    bool empty();
    QString id();
    void setTemplateBoxes(Box::List boxes);
    void appendTemplateBoxes(std::shared_ptr<Box> box);
    Box::List getTemplateBoxes() const;
    void setPageNumber(int pagenumber);
    int PageNumber() const;

private:
    Box::List mBoxes;
    Box::List mTemplateBoxes;
    QString mId;
    int mPageNumber = -1;
};

Q_DECLARE_METATYPE(std::shared_ptr<Frame>)
