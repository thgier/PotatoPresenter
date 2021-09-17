#ifndef POTATOERRORLISTENER_H
#define POTATOERRORLISTENER_H

#include "antlr4-runtime.h"
#include "potatoLexer.h"
#include "potatoParser.h"

struct SyntaxError {
    size_t line, column;
    std::string message;
};

class PotatoErrorListener : public antlr4::BaseErrorListener
{
public:
    PotatoErrorListener();
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
          const std::string &msg, std::exception_ptr e) override;
    bool success();

private:
    SyntaxError mError;
    bool mSuccess = true;

};

#endif // POTATOERRORLISTENER_H
