#include "tokenizer.h"

Tokenizer::Tokenizer()
{

}

void Tokenizer::loadInput(QIODevice *input){
    if (!input->open(QIODevice::ReadOnly))
    {
        return;
    }
    mText = input->readAll();
    mPos = 0;
}

void Tokenizer::loadInput(QByteArray input){
    mText = input;
    mPos = 0;
}

QByteArray Tokenizer::readCmdText(){
    QByteArray command = "";
    while(mText[mPos] != ' ' && mText[mPos] != '\n' && mPos < mText.size()){
        command += mText[mPos];
        mPos++;
    }
    mPos++;
    return command;
}

Token Tokenizer::readText(){
    Token ret;
    QByteArray text = "";
    bool multiline = false;
    while(mText[mPos] != '\\' && !(mText[mPos] == '\n' && mText[mPos+1] == '\\') && mPos < mText.size())
    {
        if(mText[mPos] == '\n' ) {
            multiline = true;
        }
        text += mText[mPos];
        mPos++;
    }
    ret.mText = text;
    if(multiline){
        ret.mKind = Token::Kind::MultiLineText;
    } else{
        ret.mKind = Token::Kind::Text;
    }
    if(mText[mPos] == '\n'){
        mPos++;
    }
    return ret;
}

Token Tokenizer::next(){
    Token ret;
    if (mPos < mText.size())
    {
        auto const ch = mText[mPos];
        if (ch == '\\'){
            ret.mKind = Token::Kind::Command;
            ret.mText = readCmdText();
        }
        else {
            ret = readText();
        }
    }
    else{
        ret.mKind = Token::Kind::EndOfFile;
    }
    return ret;
}

Token const Tokenizer::peekNext() {
    Tokenizer copyTokenizer(*this);
    return copyTokenizer.next();
}
