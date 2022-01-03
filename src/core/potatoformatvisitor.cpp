/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "potatoformatvisitor.h"
#include "box.h"
#include "imagebox.h"
#include "markdowntextbox.h"
#include "plaintextbox.h"
#include "codebox.h"
#include "geometrybox.h"
#include "latexbox.h"

namespace  {

    QString addBracketsToVariable(QString variable) {
        return "%{" + variable + "}";
    }

    bool multilineText(QString text) {
        return text.contains("\n");
    }

    void removeSpacesAtBack(QString &text) {
        while(!text.isEmpty() && text.back() ==' ') {
            text.chop(1);
        }
    }

    void removeBrackets(QString &text) {
        text.chop(2);
        text.remove(0, 2);
    }

    void setClassIfEmpty(QString const& boxClass, PropertyEntry const& defaultClassEntry, Box::Properties & properties) {
        if(boxClass.isEmpty()) {
            properties["class"] = defaultClassEntry;
        }
    }

    QString getValueAsQStringForProperty(QString const& property, Box::Properties & properties) {
        if(properties.find(property) != properties.end()) {
            return properties.find(property)->second.mValue;
        }
        return {};
    }

}

PotatoFormatVisitor::PotatoFormatVisitor(potatoParser &parser)
    : mParser(parser)
{
}

void PotatoFormatVisitor::enterCommand(potatoParser::CommandContext *ctx) {
    mCommand = QString::fromStdString(ctx->WORD()->getText());
}

void PotatoFormatVisitor::enterText(potatoParser::TextContext * ctx) {
    mText = QString::fromStdString(mParser.getTokenStream()->getText(ctx));
    removeSpacesAtBack(mText);
}

void PotatoFormatVisitor::enterText_in_bracket(potatoParser::Text_in_bracketContext * ctx) {
    mText = QString::fromStdString(mParser.getTokenStream()->getText(ctx));
    removeBrackets(mText);
}

void PotatoFormatVisitor::PotatoFormatVisitor::exitBox(potatoParser::BoxContext * ctx) {
    // read out values
    auto const command = mCommand;
    auto const text = mText;
    mCommand = "";
    mText = "";
    // editor start at line 0, antlr starts at line 1
    auto const line = int(ctx->getStart()->getLine()) - 1;

    if(command.isEmpty()) {
        throw ParserError{"Expected command.", line};
    }

    if(command == "slide"){
        newSlide(text, line);
        mLastCommandSetVariable = false;
        mInPreamble = false;
        mProperties.clear();
        return;
    }

    if(mInPreamble) {
        readPreambleCommand(command, text, line);
        return;
    }

    if(mSlideList.empty()){
        throw ParserError{"Expected \\slide", line};
        return;
    }

    if(command == "section") {
        mLastCommandSetVariable = true;
        setSection(text, line);
        return;
    }
    else if(command == "setvar"){
        mLastCommandSetVariable = true;
        setVariable(text, line);
        return;
    }
    else {
        mLastCommandSetVariable = false;
    }
    qInfo() << "command" << command;
    static auto const boxInstructions = std::set<QString>{"text", "image", "body", "title", "blindtext", "plaintext", "code", "geometry", "latex", "tableofcontents"};
    if(boxInstructions.find(command) != boxInstructions.end()) {
        if(mLastCommandSetVariable) {
            throw ParserError{"Command \\setvar only valid outside a slide.", line};
        }

        createNewBox(command, text, line);
        mProperties.clear();
        return;
    }


    if(command == "pause"){
        if(mParsingTemplate) {
            throw ParserError{QString("Invalid command '%1' in template").arg(command), line};
        }
        applyPause(text);
        return;
    }


    throw ParserError{QString("Invalid command '%1'").arg(command), line};
}


void PotatoFormatVisitor::exitProperty_entry(potatoParser::Property_entryContext * ctx) {
    auto const line = int(ctx->getStart()->getLine()) - 1;
    auto const property = QString::fromStdString(ctx->property()->WORD()->getText());
    auto const value = QString::fromStdString(ctx->value()->getText());
    if(property.isEmpty()) {
        throw ParserError{"Expected property.", line};
    }
    if(value.isEmpty()) {
        throw ParserError{"Expected value.", line};
    }
    mProperties[property] = {value, line};
}

void PotatoFormatVisitor::newSlide(QString id, int line) {
    if(multilineText(id)) {
        throw ParserError {"One line text expected.", line};
    }
//  reset and create new slide
    mPauseCount = 0;
    if(id.isEmpty()) {
        throw ParserError{QString("Slide id is missing.").arg(id), line};
    }
    if(mSlideList.findSlide(id)) {
        throw ParserError{QString("Slide id %1 already exists.").arg(id), line};
    }
    mSlideList.appendSlide(std::make_shared<Slide>(id, line));
    if(mProperties.find("class") != mProperties.end()) {
        mSlideList.lastSlide()->setSlideClass(mProperties.find("class")->second.mValue);
    }
    if (mProperties.find("defineclass") != mProperties.end()) {
        mSlideList.lastSlide()->setDefinesClass(mProperties.find("defineclass")->second.mValue);
    }
    // set variables
    mSlideList.lastSlide()->setVariables(mVariables);
    mSlideList.lastSlide()->setPagenumber(mSlideList.vector.size());
    if(mVariables.find("%{date}") == mVariables.end()){
        mSlideList.lastSlide()->setVariable("%{date}", QDate::currentDate().toString());
    }
    if(mVariables.find("%{resourcepath}") == mVariables.end()){
        mSlideList.lastSlide()->setVariable("%{resourcepath}", mResourcepath);
    }
    mProperties.clear();
}

void PotatoFormatVisitor::setVariable(QString text, int line) {
    auto list = QString(text).split(" ");
    auto const variable = list[0];
    list.removeFirst();
    auto const value = list.join(" ");
    // try if the value is a property if not a Parser error get thrown, in this case append to variables
    mVariables[addBracketsToVariable(variable)] = value;
}

void PotatoFormatVisitor::setSection(QString section, int line) {
    mVariables[addBracketsToVariable("section")] = section;
}

void PotatoFormatVisitor::createNewBox(QString command, QString text, int line) {
    if(!text.isEmpty()) {
        mProperties["text"] = {text, line};
    }
    std::shared_ptr<Box> box;
    QString boxClass;
    if(mProperties.find("class") != mProperties.end()) {
        boxClass = mProperties.find("class")->second.mValue;
    }
    if(command == "text"){
        box = std::make_shared<MarkdownTextBox>();
    }
    else if(command == "image"){
        if(multilineText(text)) {
            throw ParserError {"One line text expected.", line};
        }
        box = std::make_shared<ImageBox>();
        setClassIfEmpty(boxClass, {"image", line}, mProperties);
    }
    else if(command == "code"){
        box = std::make_shared<CodeBox>();
        setClassIfEmpty(boxClass, {"code", line}, mProperties);
    }
    else if(command == "body"){
        box = std::make_shared<MarkdownTextBox>();
        mProperties["class"] = {"body", line};
    }
    else if(command == "title"){
        box = std::make_shared<MarkdownTextBox>();
        mProperties["class"] = {"title", line};
    }
    else if (command == "blindtext") {
        text = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
        box = std::make_shared<MarkdownTextBox>();
    }
    else if (command == "plaintext") {
        box = std::make_shared<PlainTextBox>();
    }
    else if (command == "geometry") {
        box = std::make_shared<GeometryBox>();
    }
    else if (command == "latex") {
        box = std::make_shared<LaTeXBox>();
        setClassIfEmpty(boxClass, {"body", line}, mProperties);
    }
    else if (command == "tableofcontents") {
        box = std::make_shared<MarkdownTextBox>();
        mProperties["class"] = {"tableofcontents", line};
    }

    auto newBoxClass = getValueAsQStringForProperty("class", mProperties);
    if(newBoxClass.isEmpty()) {
        newBoxClass = "default";
    }
    auto id = getValueAsQStringForProperty("id", mProperties);
    if(id.isEmpty()) {
        id = generateId(command, newBoxClass);
    }
    else if (mBoxIds.find(id) != mBoxIds.end()) {
        throw ParserError {"Duplicated box ID.", line};
    }

    box->setProperties(mProperties);

    box->setId(id);
    box->setLine(line);
    if(mProperties.find("defineclass") != mProperties.end()) {
        box->setDefinesClass(mProperties.find("defineclass")->second.mValue);
    }
    box->setPauseCounter(mPauseCount);
    if(!getValueAsQStringForProperty("text", mProperties).isEmpty()) {
        box->style().mText = getValueAsQStringForProperty("text", mProperties);
    }

    mSlideList.lastSlide()->appendBox(box);
}


QString PotatoFormatVisitor::generateId(QString type, QString boxclass) {
    auto const slideId = mSlideList.lastSlide()->id();
    int boxCounter = 0;
    auto id = "intern-" + slideId + "-" + type + "-" + boxclass + "-0";
    while(mBoxIds.find(id) != mBoxIds.end()) {
        boxCounter++;
        id = "intern-" + slideId + "-" + type + "-" + boxclass + "-" + QString::number(boxCounter);
    }
    mBoxIds.insert(id);
    return id;
}

SlideList PotatoFormatVisitor::slides() const {
    return mSlideList;
}

Preamble PotatoFormatVisitor::preamble() const {
    return mPreamble;
}

void PotatoFormatVisitor::setDirectory(QString directory) {
    mResourcepath = directory;
}

void PotatoFormatVisitor::setParseTemplate(bool isTemplate) {
    mParsingTemplate = isTemplate;
}

void PotatoFormatVisitor::applyPause(QString text) {
    mPauseCount++;

    if(mSlideList.lastSlide()->boxes().empty()) {
        return;
    }
    auto const lastTextBox = std::dynamic_pointer_cast<TextBox>(mSlideList.lastSlide()->boxes().back());
    if(!lastTextBox) {
        return;
    }
    lastTextBox->setPauseMode(PauseDisplayMode::onlyInPause);

    auto box = std::static_pointer_cast<TextBox>(lastTextBox->clone());
    if(!text.isEmpty() && !box->text().isEmpty())
        text.insert(0, '\n');
    box->setProperty("text", {lastTextBox->text() + text, box->line()});
    box->style().mText = lastTextBox->text() + text;
    box->setPauseCounter(mPauseCount);
    lastTextBox->setId(lastTextBox->configId() + "-" + mPauseCount);
    lastTextBox->setConfigId(box->id());
    box->setPauseMode(PauseDisplayMode::fromPauseOn);
    mSlideList.vector.back()->appendBox(box);
}

void PotatoFormatVisitor::exitPotato(potatoParser::PotatoContext * /*ctx*/) {
    auto const totalNumberOfPages = mSlideList.numberSlides();
    for (auto const & slide : mSlideList.vector) {
        slide->setTotalNumberPages(totalNumberOfPages);
    }
}

void PotatoFormatVisitor::readPreambleCommand(QString command, QString text, int line) {
    if(command == "usetemplate") {
        if(!mParsingTemplate) {
            mPreamble = Preamble{text, line};
        }
        else {
            throw ParserError{QString("Unexpected command %1 in template.").arg(command), line};
        }
    }
    else if(command == "setvar") {
        setVariable(text, line);
    }
    else {
        throw ParserError{QString("Unexpected command %1.").arg(command), line};
    }
}
