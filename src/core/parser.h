#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <vector>
#include<QString>
#include "frame.h"
#include "configboxes.h"
#include "tokenizer.h"
#include "layout.h"
#include "template.h"

struct ParserError{
    QString message;
    int line;
};



using FrameList = std::vector<std::shared_ptr<Frame>>;
class Parser
{
public:
    Parser();
    void loadInput(QIODevice *input, ConfigBoxes* configuration);
    void loadInput(QByteArray input, ConfigBoxes* configuration);
    FrameList readInput();
    void setTemplate(Template &thisTemplate);
    void setFileIsATemplate(bool fileIsATemplate);
    void setVariables(std::map<QString, QString> variables);
    std::map<QString, QString> Variables() const;

private:
    void loadTemplate(int line);
    void command(Token token);
    void newFrame(int line);
    void newTextField(int line);
    void newImage(int line);
    void newTitle(int line);
    void newArrow(int line);
    void newLine(int line);
    void newPlainText(int line);
    void newBlindText(int line);
    void setVariable(int line);
    QString addBracketsToVariable(QString variable) const;
    BoxGeometry const getRect(QString id);
    BoxStyle readArguments(QString &id, QString BoxStyleIdentifier);
    QString generateId();

    Tokenizer mTokenizer;
    ConfigBoxes* mConfigBoxes;
    int mBoxCounter = 0;
    FrameList mFrames;
    std::shared_ptr<Layout> mLayout;
    std::vector<QString> mUserIds;
    std::map<QString, QString> mVariables;
    std::shared_ptr<Template> mTemplate;
    bool mParsingTemplate = false;
    int mPauseCount = 0;
};

#endif // PARSER_H
