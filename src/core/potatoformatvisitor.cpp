#include "potatoformatvisitor.h"
#include "box.h"
#include "imagebox.h"
#include "markdowntextbox.h"
#include "arrowbox.h"
#include "plaintextbox.h"
#include "linebox.h"
#include "codebox.h"

namespace  {

    QString addBracketsToVariable(QString variable) {
        return "%{" + variable + "}";
    }

}

PotatoFormatVisitor::PotatoFormatVisitor()
{

}

void PotatoFormatVisitor::enterText(potatoParser::TextContext * ctx) {
    mText = QString::fromStdString(ctx->getText());
}

void PotatoFormatVisitor::enterText_in_bracket(potatoParser::Text_in_bracketContext * ctx) {
    mText = QString::fromStdString(ctx->getText());
}

void PotatoFormatVisitor::PotatoFormatVisitor::exitBox(potatoParser::BoxContext * ctx) {
    // read out values
    auto const command = QString::fromStdString(ctx->command()->TEXT()->getText());
    auto const text = mText;
    mText = "";
    // editor start at line 0, antlr starts at line 1
    auto const line = int(ctx->getStart()->getLine()) - 1;

    if(command == "slide"){
        newSlide(text, line);
        mLastCommandSetVariable = false;
        mInPreamble = false;
        mCurrentBoxStyle = BoxStyle();
        return;
    }

    if(mInPreamble) {
        readPreambleCommand(command, text, line);
        return;
    }

    if(mSlideList.empty()){
        throw ParserError{"Expecting \\slide", line};
        return;
    }

    if(command == "setvar"){
        mLastCommandSetVariable = true;
        setVariable(text, line);
        return;
    }
    else {
        mLastCommandSetVariable = false;
    }
    qInfo() << "command" << command;
    auto const boxInstructions = std::set<QString>{"text", "image", "body", "title", "arrow", "line", "blindtext", "plaintext", "code"};
    if(boxInstructions.find(command) != boxInstructions.end()) {
        if(mLastCommandSetVariable) {
            throw ParserError{"Command \\setvar only valid outside a slide.", line};
        }

        createNewBox(command, text, line);
        mCurrentBoxStyle = BoxStyle();
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

void PotatoFormatVisitor::enterProperty(potatoParser::PropertyContext *ctx) {
    mProperty = QString::fromStdString(ctx->getText());
}

void PotatoFormatVisitor::enterValue(potatoParser::ValueContext *ctx) {
    mValue = QString::fromStdString(ctx->getText());
}

void PotatoFormatVisitor::exitProperty_entry(potatoParser::Property_entryContext * ctx) {
    auto const line = int(ctx->getStart()->getLine()) - 1;
    if(mProperty.isEmpty()) {
        throw ParserError{"Expecting property.", line};
    }

    mCurrentBoxStyle = applyProperty(mCurrentBoxStyle, mProperty, mValue, line);
    mValue = "";
    mProperty = "";
}

BoxStyle PotatoFormatVisitor::applyProperty(BoxStyle &boxstyle, QString property, QString value, int line) {
    bool numberOk = true;

    if(property == "defineclass") {
        boxstyle.mDefineclass = value;
    }
    else if(property == "color"){
        QColor color;
        color.setNamedColor(QString(value));
        if(!color.isValid()) {
            throw ParserError{QString("Invalid color '%1'").arg(QString(value)), line};
        }
        boxstyle.mColor = color;
    }
    else if(property == "opacity"){
        boxstyle.mOpacity = value.toDouble(&numberOk);
    }
    else if(property == "font-size"){
        boxstyle.mFontSize = value.toInt(&numberOk);
    }
    else if(property == "line-height"){
        if(value.toDouble() != 0){
            boxstyle.mLineSpacing = value.toDouble(&numberOk);
        }
    }
    else if(property == "font-weight"){
        if(QString(value) == "bold"){
            boxstyle.mFontWeight = FontWeight::bold;
        }
        else if(QString(value) == "normal"){
            boxstyle.mFontWeight = FontWeight::normal;
        }
        else{
            throw ParserError{"Invalid value for 'font-weight' (possible values: bold, normal)", line};
        }
    }
    else if(property == "font"){
        boxstyle.mFont = QString(value);
    }
    else if(property == "id"){
        boxstyle.mId = value;
        if(value.startsWith("intern")) {
            throw ParserError{"User defined box IDs must not start with \"intern\"", line};
        }
        if(mBoxIds.find(value) != mBoxIds.end()) {
            throw ParserError{"Duplicate box ID", line};
        }
        mBoxIds.insert(value);
    }
    else if(property == "left"){
        boxstyle.mGeometry.setLeft(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "top"){
        boxstyle.mGeometry.setTop(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "width"){
        boxstyle.mGeometry.setWidth(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "height"){
        boxstyle.mGeometry.setHeight(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "angle"){
        boxstyle.mGeometry.setAngle(value.toDouble(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "movable"){
        if(value == "true") {
            boxstyle.movable = true;
        }
        else if(value == "false") {
            boxstyle.movable = false;
        }
        else {
            throw ParserError{"Invalid value for 'movable' (possible values: true, false)", line};
        }
    }
    else if(property == "text-align"){
        if(value == "left") {
            boxstyle.mAlignment = Qt::AlignLeft;
        }
        else if(value == "right") {
            boxstyle.mAlignment = Qt::AlignRight;
        }
        else if(value == "center") {
            boxstyle.mAlignment = Qt::AlignCenter;
        }
        else if(value == "justify") {
            boxstyle.mAlignment = Qt::AlignJustify;
        }
        else {
            throw ParserError{"Invalid value for 'text-align' (possible values: left, right, center, justify)", line};
        }
    }
    else if(property == "class"){
        boxstyle.mClass = value;
    }
    else if(property == "language"){
        boxstyle.language = QString(value);
    }
    else if(property == "background"){
        QColor color;
        color.setNamedColor(value);
        if(!color.isValid()) {
            throw ParserError{"Invalid color", line};
        }
        boxstyle.mBackgroundColor = color;
    }
    else if(property == "background-color"){
        QColor color;
        color.setNamedColor(value);
        if(!color.isValid()) {
            throw ParserError{"Invalid color", line};
        }
        boxstyle.mBackgroundColor = color;
    }
    else if(property == "padding") {
        boxstyle.mPadding = value.toInt(&numberOk);
    }
    else if(property == "border"){
        auto values = QString(value).split(" ");
        if(values.empty()) {
            return {};
        }
        if(values[0].endsWith("px") && values.length() >= 2) {
            auto value = values[0];
            value.chop(2);
            bool ok;
            boxstyle.mBorder.width = value.toInt(&ok);
            if(!ok) {
                throw ParserError{"Invalid width value for 'border'", line};
            }
            boxstyle.mBorder.style = values[1];
            if(values.length() >= 3) {
                boxstyle.mBorder.color = QColor(QString(values[2]));
            }
        }
        else {
            boxstyle.mBorder.style = values[0];
            if(values.length() >= 2) {
                boxstyle.mBorder.color = QColor(QString(values[1]));
            }
        }
    }
    else {
        throw ParserError{QString("Invalid Argument %1.").arg(property), line};
    }
    if(!numberOk) {
        throw ParserError{"Invalid number", line};
    }
    return boxstyle;
}

void PotatoFormatVisitor::exitPotato(potatoParser::PotatoContext * /*ctx*/) {
    auto const totalNumberOfPages = mSlideList.numberSlides();
    for (auto const & slide : mSlideList.vector) {
        slide->setVariable("%{totalpages}", QString::number(totalNumberOfPages));
    }
}

void PotatoFormatVisitor::readPreambleCommand(QString command, QString text, int line) {
    if(command == "usetemplate") {
        if(!mParsingTemplate) {
            mPreamble = Preamble{text};
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

void PotatoFormatVisitor::newSlide(QString id, int line) {
//  reset and create new slide
    mPauseCount = 0;
    if(id.isEmpty()) {
        throw ParserError{QString("Slide id is missing.").arg(id), line};
    }
    if(mSlideList.findSlide(id)) {
        throw ParserError{QString("Slide id %1 already exists.").arg(id), line};
    }
    mSlideList.appendSlide(std::make_shared<Slide>(id, line));
    mSlideList.lastSlide()->setSlideClass(mCurrentBoxStyle.getClass());

    mSlideList.lastSlide()->setDefinesClass(mCurrentBoxStyle.mDefineclass.value_or(""));

    // set variables
    mSlideList.lastSlide()->setVariables(mVariables);
    mSlideList.lastSlide()->setStandardBoxStyle(mStandardBoxStyle);
    mSlideList.lastSlide()->setVariable("%{pagenumber}", QString::number(mSlideList.vector.size()));
    if(mVariables.find("%{date}") == mVariables.end()){
        mSlideList.lastSlide()->setVariable("%{date}", QDate::currentDate().toString());
    }
    if(mVariables.find("%{resourcepath}") == mVariables.end()){
        mSlideList.lastSlide()->setVariable("%{resourcepath}", mResourcepath);
    }
}

void PotatoFormatVisitor::setVariable(QString text, int line) {
    auto const list = text.split(QRegularExpression("\\s+"));
    auto const variable = list[0];
    auto const value = text.right(text.size() - variable.size() - 1);
    // try if the value is a property if not a Parser error get thrown, in this case append to variables
    try {
        mStandardBoxStyle = applyProperty(mStandardBoxStyle, variable, value, line);
    }  catch (ParserError) {
        mVariables[addBracketsToVariable(variable)] = value;
    }

}

void PotatoFormatVisitor::createNewBox(QString command, QString text, int line) {
    QString id = mCurrentBoxStyle.id();
    if(id.isEmpty()) {
        mCurrentBoxStyle.mId = generateId("text", mCurrentBoxStyle.getClass());
    }
    std::shared_ptr<Box> box;
    if(command == "text"){
        box = std::make_shared<MarkdownTextBox>(text);
    }
    else if(command == "image"){
        box = std::make_shared<ImageBox>(text);
        if(!mCurrentBoxStyle.mClass.has_value()) {
            mCurrentBoxStyle.mClass = "body";
        }
    }
    else if(command == "code"){
        box = std::make_shared<CodeBox>(text);
        if(!mCurrentBoxStyle.mClass.has_value()) {
            mCurrentBoxStyle.mClass = "body";
        }
    }
    else if(command == "body"){
        box = std::make_shared<MarkdownTextBox>(text);
        mCurrentBoxStyle.mClass = "body";
    }
    else if(command == "title"){
        if(text.isEmpty()) {
            text = mSlideList.lastSlide()->id();
        }
        box = std::make_shared<MarkdownTextBox>(text);
        mCurrentBoxStyle.mClass = "title";
    }
    else if(command == "arrow"){
        box = std::make_shared<ArrowBox>();
    }
    else if(command == "line"){
        box = std::make_shared<LineBox>();
    }
    else if (command == "blindtext") {
        text = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
        box = std::make_shared<MarkdownTextBox>(text);
    }
    else if (command == "plaintext") {
        box = std::make_shared<PlainTextBox>(text);
    }
    mCurrentBoxStyle.mLine = line;
    box->setBoxStyle(mCurrentBoxStyle);
    box->setPauseCounter(mPauseCount);
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

    auto const lastTextBox = std::dynamic_pointer_cast<TextBox>(mSlideList.lastSlide()->boxes().back());
    if(!lastTextBox) {
        return;
    }

    auto box = lastTextBox->clone();
    text.insert(0, '\n');
    box->appendText(text);
    box->setPauseCounter(mPauseCount);
    mSlideList.vector.back()->appendBox(box);

    lastTextBox->setConfigId(lastTextBox->id());
    lastTextBox->setPauseMode(PauseDisplayMode::onlyInPause);
    lastTextBox->setId(generateId("text", lastTextBox->style().getClass()));
}
