#pragma once

#include <vector>
#include <QVariant>
#include "box.h"

class Slide
{
public:
    using Ptr = std::shared_ptr<Slide>;

    Slide();
    Slide(QString const& id, std::map<QString, QString> const& variables, int line);

    // Access contained boxes
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);
    void appendBox(std::shared_ptr<Box> box);
    Box::List const& boxes() const;
    bool empty();
    Box::Ptr findBox(QString const& id) const;
    bool containsBox(QString const& id) const;

    // Returns the max PauseCounter of the boxes
    int numberPauses() const;

    // line in which the "\slide" comment is written in the input file
    int line() const;

    // Template boxes are rendered in the background of the slide.
    void setTemplateBoxes(Box::List boxes);
    void appendTemplateBoxes(Box::Ptr box);
    Box::List templateBoxes() const;

    // The slide ID is the string after the "\slide" command, and is used to track
    // the slide when the document changes.
    QString const& id() const;

    // Access to this slide's variables
    void setVariables(Variables const& variables);
    void setVariable(QString const& name, QString const& value);
    Variables const& variables() const;

    void setSlideClass(QString const& slideClass);
    QString const& slideClass() const;

private:
    Box::List mBoxes;
    Box::List mTemplateBoxes;
    QString mId;
    Variables mVariables;
    QString mClass;
    int mLine;
};

Q_DECLARE_METATYPE(Slide::Ptr)
