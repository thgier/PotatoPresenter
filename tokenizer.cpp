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
    mIsAtStartOfLine = true;
    mLine = 0;
}

void Tokenizer::loadInput(QByteArray input){
    mText = input;
    mPos = 0;
    mIsAtStartOfLine = true;
    mLine = 0;
}

QByteArray Tokenizer::readCmdText(){
    mIsAtStartOfLine = false;
    QByteArray command = "";
    while(mText[mPos] != ' ' && mText[mPos] != '\n' && mPos < mText.size() && mText[mPos] != '['){
        command += mText[mPos];
        mPos++;
    }
    if(mText[mPos] == ' '){
        mPos++;
    }
    return removeSpacesNewLines(command);
}

Token Tokenizer::readText(){
    Token ret;
    ret.mLine = mLine;
    QByteArray text = "";
    bool multiline = false;
    while(!(mText[mPos] == '\n' && mText[mPos+1] == '\\')
            && !(mText[mPos] == '\n' && mText[mPos+1] == '\n')
            && !(mText[mPos] == '\n' && mPos+1 >= mText.size())
            && mPos < mText.size())
    {
        if(mText[mPos] == '\n' ) {
            multiline = true;
            mLine++;
        }
        text += mText[mPos];
        mPos++;
    }
    ret.mText = removeSpacesNewLines(text);
    if(multiline){
        ret.mKind = Token::Kind::MultiLineText;
    } else{
        ret.mKind = Token::Kind::Text;
    }
    if(mText[mPos] == '\n'){
        mPos++;
        mIsAtStartOfLine = true;
        mLine++;
    }
    else{
        mIsAtStartOfLine = false;
    }
    if(mText[mPos] == '\n'){
        mPos++;
        mLine++;
    }
    return ret;
}

Token Tokenizer::readArgument(){
    Token ret;
    ret.mKind = Token::Kind::Argument;
    ret.mLine = mLine;
    QByteArray text = "";
    while(mText[mPos] != ':' && mPos < mText.size()){
        text.append(mText[mPos]);
        mPos++;
    }
    mPos++;
    ret.mText = removeSpacesNewLines(text);
    return ret;
}

Token Tokenizer::readArgumentValue(){
    Token ret;
    ret.mKind = Token::Kind::ArgumentValue;
    ret.mLine = mLine;
    QByteArray text = "";
    while(mText[mPos] != ';' && mText[mPos] != ']' && mPos < mText.size()){
        text.append(mText[mPos]);
        mPos++;
    }
    if(mText[mPos] == ']'){
        mInArgumentList = false;
    }
    mPos++;
    ret.mText = removeSpacesNewLines(text);
    return ret;
}

Token Tokenizer::next(){
    Token ret;
    if (mPos < mText.size())
    {
        auto const ch = mText[mPos];
        if (ch == '\\' && mIsAtStartOfLine){
            ret.mKind = Token::Kind::Command;
            ret.mText = readCmdText();
            ret.mLine = mLine;
            mLastItemCommand = true;
        }
        else if (ch == '[' && mLastItemCommand){
            mPos++;
            mLastItemCommand = false;
            mInArgumentList = true;
            ret = readArgument();
            mExpectArgumentValue = true;
        }
        else if (mExpectArgumentValue){
            ret = readArgumentValue();
            mExpectArgumentValue = false;
        }
        else if(mInArgumentList){
            ret = readArgument();
            mExpectArgumentValue = true;
        }
        else {
            ret = readText();
            mLastItemCommand = false;
        }
    }
    else{
        ret.mKind = Token::Kind::EndOfFile;
    }
    if(ret.mText.isEmpty() && ret.mKind != Token::Kind::EndOfFile){
        ret = next();
    }
    return ret;
}

QByteArray Tokenizer::removeSpacesNewLines(QByteArray text) const{
    if(text.isEmpty()) {
        return {};
    }
    while(text.front() == ' ' || text.front() == '\n'){
        text = text.mid(1);
    }
    if(text.isEmpty()) {
        return {};
    }
    while(text.back() == ' ' || text.back() == '\n'){
        text.chop(1);
    }
    return text;
}

Token Tokenizer::peekNext() const {
    Tokenizer copyTokenizer(*this);
    return copyTokenizer.next();
}


