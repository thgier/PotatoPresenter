#pragma once

#include <vector>
#include <QVariant>
#include "box.h"

class Frame
{
public:
    using Ptr = std::shared_ptr<Frame>;

    Frame();
    Frame(QString const& id, std::map<QString, QString> const& variables, int line);

    // Access contained boxes
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);
    void appendBox(std::shared_ptr<Box> box);
    Box::List const& boxes() const;
    bool empty();
    Box::Ptr findBox(QString const& id) const;
    bool containsBox(QString const& id) const;

    // Returns the max PauseCounter of the boxes
    int numberPauses() const;

    // line in which the "\frame" comment is written in the input file
    int line() const;

    // Template boxes are rendered in the background of the frame.
    void setTemplateBoxes(Box::List boxes);
    void appendTemplateBoxes(Box::Ptr box);
    Box::List templateBoxes() const;

    // The frame ID is the string after the "\frame" command, and is used to track
    // the frame when the document changes.
    QString const& id() const;

    // Access to this frame's variables
    void setVariables(Variables const& variables);
    void setVariable(QString const& name, QString const& value);
    Variables const& variables() const;

    void setFrameClass(QString const& frameClass);
    QString const& frameClass() const;

private:
    Box::List mBoxes;
    Box::List mTemplateBoxes;
    QString mId;
    Variables mVariables;
    QString mClass;
    int mLine;
};

Q_DECLARE_METATYPE(Frame::Ptr)
