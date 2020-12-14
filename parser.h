#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <vector>
#include<QString>
#include "frame.h"
#include "configboxes.h"
#include "tokenizer.h"
#include "layout.h"

using FrameList = std::vector<std::shared_ptr<Frame>>;
class Parser
{
public:
    Parser();
    void loadInput(QIODevice *input, ConfigBoxes* configuration);
    void loadInput(QByteArray input, ConfigBoxes* configuration);
    std::optional<FrameList> readJson(QString text, ConfigBoxes* configuration);
    FrameList readInput();
    void command(QByteArray text);
    void newFrame();
    void newTextField();
    void newImage();
    QRect const getRect(QString id);

private:
    Tokenizer mTokenizer;
    ConfigBoxes* mConfigBoxes;
    int mBoxCounter = 0;
    FrameList mFrames;
    Layout mLayout;
};

#endif // PARSER_H
