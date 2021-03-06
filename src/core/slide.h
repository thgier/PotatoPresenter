/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <vector>
#include <QVariant>
#include "box.h"

class Slide
{
public:
    using Ptr = std::shared_ptr<Slide>;

    Slide();
    Slide(QString const& id, int line);
    Slide(QString const& id, PresentationContext const& variables, int line);

    // Access contained boxes
    void setBoxes(std::vector<std::shared_ptr<Box>> boxes);
    void appendBox(std::shared_ptr<Box> box);
    Box::List const& boxes() const;
    bool empty();
    Box::Ptr findBox(QString const& id) const;
    Box::Ptr findDefineBoxClass(QString const& boxclass) const;
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
    Variables& variables();
    QString valueOfVariable(QString const& variable) const;
    std::optional<QString> removeVariable(QString const& variable);

    int pagenumber() const;
    void setPagenumber(int pagenumber);
    void setTotalNumberPages(int pages);

    void setSlideClass(QString const& slideClass);
    QString slideClass() const;

    void setDefinesClass(QString definesClass);
    QString definesClass() const;

    void setTableOfContents(TableOfContent tableofcontent);
    PresentationContext const& context() const;

private:
    Box::List mBoxes;
    Box::List mTemplateBoxes;
    QString mId;
    PresentationContext mContext;
    QString mClass;
    int mLine;
    BoxStyle mDefaultStyle;
    QString mDefinesClass;
};

Q_DECLARE_METATYPE(Slide::Ptr)
