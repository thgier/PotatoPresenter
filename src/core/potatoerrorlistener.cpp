#include "potatoerrorlistener.h"

PotatoErrorListener::PotatoErrorListener()
{

}


void PotatoErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
                      const std::string &msg, std::exception_ptr e) {
    mError = SyntaxError {line, charPositionInLine, msg};
    mSuccess = false;
}

bool PotatoErrorListener::success() {
    return mSuccess;
}

SyntaxError PotatoErrorListener::error() {
    return mError;
}

