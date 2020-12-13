#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <vector>
#include<QString>
#include "frame.h"
#include "configboxes.h"
#include "tokenizer.h"

enum BoxType{
    Text,
    Image
};

//struct constructBox{
//    std::shared_ptr<Frame> mFrame;
//    QString mText;
//    QString mId;
//    BoxType mType;
//    QRect mRect;
//    constructBox(std::shared_ptr<Frame> frame, QString text, int nBox, BoxType type)
//        : mFrame{frame}
//        , mText{text}
//        , mId{frame->id() + "-" + QString::number(nBox)}
//        , mType{type}
//    {
//        guessRect();
//    };

//    void guessRect(){

//        if(configuration->getRect(mId).isEmpty()){
//            mRect = QRect(50, 200, 1500, 650);
//        } else {
//            mRect = configuration->getRect(mId);
//        }
//    }
//    void addText(QString text){
//        mText += text;
//    };
//    void addToFrame(){
//        Box std::shared_ptr<box>;
//        switch (mType) {
//        case Text:
//            box = std::make_shared<TextField>(mText, mRect, mId);
//            break;
//        case Image:
//            box = std::make_shared<Image>(mText, mRect, mId);
//            break;

//        }
//    }
//};

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
    std::shared_ptr<Frame> mCurrentFrame = nullptr;
    int mBoxCounter = 0;
    FrameList mFrames;
};

#endif // PARSER_H
