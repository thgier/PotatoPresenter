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

void PotatoFormatVisitor::PotatoFormatVisitor::exitBox(potatoParser::BoxContext * ctx) {
    // read out values
    auto const command = QString::fromStdString(ctx->command()->TEXT()->getText());
    auto const text = QString::fromStdString(ctx->paragraph()->text()->getText());
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

    if(command == "\\setvar"){
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

void PotatoFormatVisitor::exitProperty_entry(potatoParser::Property_entryContext * ctx) {
    auto const property = QString::fromStdString(ctx->text_colon()->TEXT()->toString());
    auto const value = QString::fromStdString(ctx->value()->getText());
    auto const line = int(ctx->getStart()->getLine());

    bool numberOk;

    if(value.isEmpty()){
        throw ParserError{"Expecting argument value", line};
        return;
    }
    else if(property == "color"){
        QColor color;
        color.setNamedColor(QString(value));
        if(!color.isValid()) {
            throw ParserError{QString("Invalid color '%1'").arg(QString(value)), line};
        }
        mCurrentBoxStyle.mColor = color;
    }
    else if(property == "opacity"){
        mCurrentBoxStyle.mOpacity = value.toDouble(&numberOk);
    }
    else if(property == "font-size"){
        mCurrentBoxStyle.mFontSize = value.toInt(&numberOk);
    }
    else if(property == "line-height"){
        if(value.toDouble() != 0){
            mCurrentBoxStyle.mLineSpacing = value.toDouble(&numberOk);
        }
    }
    else if(property == "font-weight"){
        if(QString(value) == "bold"){
            mCurrentBoxStyle.mFontWeight = FontWeight::bold;
        }
        else if(QString(value) == "normal"){
            mCurrentBoxStyle.mFontWeight = FontWeight::normal;
        }
        else{
            throw ParserError{"Invalid value for 'font-weight' (possible values: bold, normal)", line};
        }
    }
    else if(property == "font"){
        mCurrentBoxStyle.mFont = QString(value);
    }
    else if(property == "id"){
        mCurrentBoxStyle.mId = value;
        if(value.startsWith("intern")) {
            throw ParserError{"User defined box IDs must not start with \"intern\"", line};
        }
        if(mBoxIds.find(value) != mBoxIds.end()) {
            throw ParserError{"Duplicate box ID", line};
        }
        mBoxIds.insert(value);
    }
    else if(property == "left"){
        mCurrentBoxStyle.mGeometry.setLeft(value.toInt(&numberOk));
        mCurrentBoxStyle.movable = false;
    }
    else if(property == "top"){
        mCurrentBoxStyle.mGeometry.setTop(value.toInt(&numberOk));
        mCurrentBoxStyle.movable = false;
    }
    else if(property == "width"){
        mCurrentBoxStyle.mGeometry.setWidth(value.toInt(&numberOk));
        mCurrentBoxStyle.movable = false;
    }
    else if(property == "height"){
        mCurrentBoxStyle.mGeometry.setHeight(value.toInt(&numberOk));
        mCurrentBoxStyle.movable = false;
    }
    else if(property == "angle"){
        mCurrentBoxStyle.mGeometry.setAngle(value.toDouble(&numberOk));
        mCurrentBoxStyle.movable = false;
    }
    else if(property == "movable"){
        if(value == "true") {
            mCurrentBoxStyle.movable = true;
        }
        else if(value == "false") {
            mCurrentBoxStyle.movable = false;
        }
        else {
            throw ParserError{"Invalid value for 'movable' (possible values: true, false)", line};
        }
    }
    else if(property == "text-align"){
        if(value == "left") {
            mCurrentBoxStyle.mAlignment = Qt::AlignLeft;
        }
        else if(value == "right") {
            mCurrentBoxStyle.mAlignment = Qt::AlignRight;
        }
        else if(value == "center") {
            mCurrentBoxStyle.mAlignment = Qt::AlignCenter;
        }
        else if(value == "justify") {
            mCurrentBoxStyle.mAlignment = Qt::AlignJustify;
        }
        else {
            throw ParserError{"Invalid value for 'text-align' (possible values: left, right, center, justify)", line};
        }
    }
    else if(property == "class"){
        mCurrentBoxStyle.mClass = value;
    }
    else if(property == "language"){
        mCurrentBoxStyle.language = QString(value);
    }
    else if(property == "background"){
        QColor color;
        color.setNamedColor(value);
        if(!color.isValid()) {
            throw ParserError{"Invalid color", line};
        }
        mCurrentBoxStyle.mBackgroundColor = color;
    }
    else if(property == "background-color"){
        QColor color;
        color.setNamedColor(value);
        if(!color.isValid()) {
            throw ParserError{"Invalid color", line};
        }
        mCurrentBoxStyle.mBackgroundColor = color;
    }
    else if(property == "padding") {
        mCurrentBoxStyle.mPadding = value.toInt(&numberOk);
    }
    else if(property == "border"){
        auto values = QString(value).split(" ");
        if(values.empty()) {
            return;;
        }
        if(values[0].endsWith("px") && values.length() >= 2) {
            auto value = values[0];
            value.chop(2);
            bool ok;
            mCurrentBoxStyle.mBorder.width = value.toInt(&ok);
            if(!ok) {
                throw ParserError{"Invalid width value for 'border'", line};
            }
            mCurrentBoxStyle.mBorder.style = values[1];
            if(values.length() >= 3) {
                mCurrentBoxStyle.mBorder.color = QColor(QString(values[2]));
            }
        }
        else {
            mCurrentBoxStyle.mBorder.style = values[0];
            if(values.length() >= 2) {
                mCurrentBoxStyle.mBorder.color = QColor(QString(values[1]));
            }
        }
    }
    else {
        throw ParserError{QString("Invalid Argument %1.").arg(property), line};
    }
//    if(!numberOk) {
//        throw ParserError{"Invalid number", line};
//    }
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
    mSlideList.appendSlide(std::make_shared<Slide>(id, line));
    mSlideList.lastSlide()->setSlideClass(mCurrentBoxStyle.getClass());

    // set variables
    mSlideList.lastSlide()->setVariables(mVariables);
    mSlideList.lastSlide()->setVariable("%{pagenumber}", QString::number(mSlideList.vector.size()));
//        TODO: is this the right place for this?
    if(mVariables.find("%{date}") == mVariables.end()){
        mSlideList.lastSlide()->setVariable("%{date}", QDate::currentDate().toString());
    }
    if(mVariables.find("%{resourcepath}") == mVariables.end()){
        mSlideList.lastSlide()->setVariable("%{resourcepath}", mResourcepath);
    }
}

void PotatoFormatVisitor::setVariable(QString text, int line) {
    auto list = text.split(QRegularExpression("\\s+"));
    auto variable = list[0];
    mVariables[addBracketsToVariable(variable)] = text.right(text.size() - variable.size() - 1);
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

    text.insert(0, '\n');
    auto box = lastTextBox->clone();
    box->appendText(text);
    box->setPauseCounter(mPauseCount);
    mSlideList.vector.back()->appendBox(box);

    lastTextBox->setConfigId(lastTextBox->id());
    lastTextBox->setPauseMode(PauseDisplayMode::onlyInPause);
    lastTextBox->setId(generateId("text", lastTextBox->style().getClass()));
}
