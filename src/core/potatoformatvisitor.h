#ifndef POTATOFORMATVISITOR_H
#define POTATOFORMATVISITOR_H

#include "potatoBaseListener.h"
#include "slide.h"
#include "presentation.h"

#include <QString>

struct ParserError{
    QString message;
    int line;
};

struct Preamble {
    QString templateName;
};

class PotatoFormatVisitor : public potatoBaseListener
{
public:
    PotatoFormatVisitor();

    void enterText(potatoParser::TextContext * ctx) override;
    void exitProperty_entry(potatoParser::Property_entryContext * ctx) override;
    void exitBox(potatoParser::BoxContext * /*ctx*/) override;
    void exitPotato(potatoParser::PotatoContext * /*ctx*/) override;

    void setDirectory(QString directory);
    void applyPause(QString text);

//    acess varibles
    SlideList slides() const;
    Preamble preamble() const;
    void setParseTemplate(bool isTemplate);
    void setVariables(std::map<QString, QString> variables);
    std::map<QString, QString> Variables() const;

private:
    void newSlide(QString id, int line);

    void readPreambleCommand(QString command, QString text, int line);

//    create new Box
    void createNewBox(QString command, QString text, int line);

    void setVariable(QString text, int line);
    QString generateId(QString type, QString boxclass);

private:
    SlideList mSlideList;
    std::set<QString> mBoxIds;

    QString mResourcepath;

    bool mParsingTemplate = false;
    int mPauseCount = 0;
    Preamble mPreamble;

    bool mInProbertyList = false;
    bool mLastCommandSetVariable = false;
    bool mInPreamble = true;
    QString mText = "";

    BoxStyle mCurrentBoxStyle;
    std::map<QString, QString> mVariables;
};

#endif // POTATOFORMATVISITOR_H
