#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <vector>
#include<QString>
#include "frame.h"
#include "configboxes.h"
#include "tokenizer.h"
#include "presentation.h"

struct ParserError{
    QString message;
    int line;
};

struct Preamble {
    QString templateName;
};

class Parser
{
public:
    Parser(QString resourcepath);
    void loadInput(QIODevice *input);
    void loadInput(QByteArray input);
    Preamble readPreamble();
    FrameList readInput();
    void setVariables(std::map<QString, QString> variables);
    std::map<QString, QString> Variables() const;

private:
    void command(Token token);
    void preambleCommand(Token token);
    void newFrame(int line);
    void newTextField(int line);
    void newImage(int line);
    void newTitle(int line);
    void newBody(int line);
    void newArrow(int line);
    void newLine(int line);
    void newPlainText(int line);
    void newBlindText(int line);
    void setVariable(int line);
    QString addBracketsToVariable(QString variable) const;
    BoxStyle readArguments(QString &id);
    QString generateId();

    Tokenizer mTokenizer;
    int mBoxCounter = 0;
    FrameList mFrameList;
    std::vector<QString> mUserIds;
    std::map<QString, QString> mVariables;
    bool mParsingTemplate = false;
    int mPauseCount = 0;
    Preamble mPreamble;
    QString mResourcepath;
};

#endif // PARSER_H
