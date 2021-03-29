/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QString>
#include <QIODevice>

struct Token {
    enum class Kind {
        Command,
        Argument,
        ArgumentValue,
        Text,
        MultiLineText,
        EndOfFile
    };
    Kind mKind;
    QByteArray mText;   
    int mLine;
};

class Tokenizer
{
public:
    Tokenizer();
    void loadInput(QIODevice *input);
    void loadInput(QByteArray input);
    Token next();
    Token peekNext() const;
private:
    Token readText();
    Token readArgument();
    Token readArgumentValue();
    QByteArray readCmdText();

    QByteArray removeSpacesNewLines(QByteArray text) const;

    QByteArray mText;
    int mPos = 0;
    bool mIsAtStartOfLine = true;
    int mLine = 0;
    bool mLastItemCommand = false;
    bool mInArgumentList = false;
    bool mExpectArgumentValue = false;
};

#endif // TOKENIZER_H
