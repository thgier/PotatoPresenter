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
    Frame(QString id, std::map<QString, QString> variables);
    Box::List getBoxes() const;
    std::shared_ptr<Box> getBox(QString id) const;
    bool containsBox(QString id) const;
    void appendBox(std::shared_ptr<Box> box);
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);
    bool empty();
    QString id();
    void setTemplateBoxes(Box::List boxes);
    void appendTemplateBoxes(std::shared_ptr<Box> box);
    Box::List getTemplateBoxes() const;
    void setPageNumber(int pagenumber);
    int PageNumber() const;
    void setVariables(std::map<QString, QString> variables);
    void setVariable(QString name, QString value);
    std::map<QString, QString> Variables() const;
    int NumberPause() const;
    void setNumberPause(int number);

private:
    Box::List mBoxes;
    Box::List mTemplateBoxes = {};
    QString mId;
    int mPageNumber = -1;
    std::map<QString, QString> mVariables;
    int mNumberPause = 1;
};

Q_DECLARE_METATYPE(std::shared_ptr<Frame>)
