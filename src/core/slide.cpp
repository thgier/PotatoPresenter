/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "slide.h"

Slide::Slide()
    : mId{""}
{

}

Slide::Slide(const QString &id, int line)
    : mId{id}
    , mLine{line}
{
}

Slide::Slide(const QString &id, const PresentationContext &context, int line)
    : mId{id}
    , mContext{context}
    , mLine{line}
{
}

const Box::List &Slide::boxes() const
{
    return mBoxes;
}

void Slide::appendBox(std::shared_ptr<Box> box)
{
    mBoxes.push_back(box);
}

void Slide::setBoxes(std::vector<std::shared_ptr<Box>> boxes){
    mBoxes = boxes;
}

bool Slide::empty() {
    return (mBoxes.empty() && mTemplateBoxes.empty());
}

QString const& Slide::id() const {
    return mId;
}

Box::Ptr Slide::findBox(QString const& id) const{
    for(auto const &box: boxes()){
        if(box->id() == id){
            return box;
        }
    }
    return {};
}

Box::Ptr Slide::findDefineBoxClass(QString const& boxclass) const{
    for(auto const &box: boxes()){
        auto const boxclassFromList = box->style().mDefineclass;
        if( boxclassFromList && boxclassFromList == boxclass){
            return box;
        }
    }
    return {};
}

bool Slide::containsBox(const QString &id) const{
    for(auto const &box: boxes()){
        if(box->id() == id){
            return true;
        }
    }
    return false;
}

void Slide::setTemplateBoxes(Box::List boxes){
    mTemplateBoxes = boxes;
}

void Slide::appendTemplateBoxes(Box::Ptr box){
    mTemplateBoxes.push_back(box);
}

Box::List Slide::templateBoxes() const{
    return mTemplateBoxes;
}

void Slide::setVariables(Variables const& variables){
    mContext.mVariables = variables;
}

Variables const& Slide::variables() const{
    return mContext.mVariables;
}

Variables& Slide::variables() {
    return mContext.mVariables;
}

void Slide::setVariable(QString const& name, QString const& value){
    mContext.mVariables[name] = value;
}

int Slide::numberPauses() const {
    if(mBoxes.empty()) {
        return 1;
    }
    auto const& maxBox = std::max_element(mBoxes.begin(), mBoxes.end(), [](auto const& a, auto const& b){return a->pauseCounter().mCount < b->pauseCounter().mCount;});
    return maxBox->get()->pauseCounter().mCount;
}

int Slide::line() const {
    return mLine;
}

void Slide::setSlideClass(QString const& slideClass) {
    mClass = slideClass;
}

QString Slide::slideClass() const {
    if(mClass.isEmpty()) {
        return "default";
    }
    return mClass;
}

void Slide::setDefinesClass(QString definesClass) {
    mDefinesClass = definesClass;
}

QString Slide::definesClass() const {
    return mDefinesClass;
}

QString Slide::valueOfVariable(const QString &variable) const {
    auto const value = variables().find(variable);
    if(value != variables().end()) {
        return value->second;
    }
    return {};
}

int Slide::pagenumber() const {
    return mContext.mPagenumber;
}

void Slide::setTotalNumberPages(int pages) {
    mContext.mTotalnumberofPages = pages;
    mContext.mVariables["%{totalpages}"] = QString::number(pages);
}

void Slide::setPagenumber(int pagenumber) {
    mContext.mPagenumber = pagenumber;
    mContext.mVariables["%{pagenumber}"] = QString::number(pagenumber);
}

void Slide::setTableOfContents(TableOfContent tableofcontent) {
    mContext.mTableOfContent = tableofcontent;
}

PresentationContext const& Slide::context() const {
    return mContext;
}
