#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QString>
#include <QIODevice>

struct Token {
    enum class Kind {
        Command,
        Text,
        MultiLineText,
        EndOfFile
    };
    Kind mKind;
    QByteArray mText;   
};

class Tokenizer
{
public:
    Tokenizer();
    void loadInput(QIODevice *input);
    void loadInput(QByteArray input);
    Token next();
    QByteArray readCmdText();
    Token readText();
    Token const peekNext();
private:
    QByteArray mText;
    int mPos = 0;
    bool mIsAtStartOfLine = true;
};

#endif // TOKENIZER_H
