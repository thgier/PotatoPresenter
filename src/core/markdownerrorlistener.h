#ifndef MARKDOWNERRORLISTENER_H
#define MARKDOWNERRORLISTENER_H

#include "antlr4-runtime.h"
#include "markdownLexer.h"
#include "markdownParser.h"

struct SyntaxError {
    size_t line, column;
    std::string message;
};

class MarkdownErrorListener : public antlr4::BaseErrorListener
{
public:
    MarkdownErrorListener();
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
          const std::string &msg, std::exception_ptr e) override;
    bool success();

private:
    SyntaxError mError;
    bool mSuccess = true;
};

#endif // MARKDOWNERRORLISTENER_H
