
// Generated from potato.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "potatoParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by potatoParser.
 */
class  potatoListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterPotato(potatoParser::PotatoContext *ctx) = 0;
  virtual void exitPotato(potatoParser::PotatoContext *ctx) = 0;

  virtual void enterBox(potatoParser::BoxContext *ctx) = 0;
  virtual void exitBox(potatoParser::BoxContext *ctx) = 0;

  virtual void enterCommand(potatoParser::CommandContext *ctx) = 0;
  virtual void exitCommand(potatoParser::CommandContext *ctx) = 0;

  virtual void enterProperty_entry(potatoParser::Property_entryContext *ctx) = 0;
  virtual void exitProperty_entry(potatoParser::Property_entryContext *ctx) = 0;

  virtual void enterValue(potatoParser::ValueContext *ctx) = 0;
  virtual void exitValue(potatoParser::ValueContext *ctx) = 0;

  virtual void enterParagraph(potatoParser::ParagraphContext *ctx) = 0;
  virtual void exitParagraph(potatoParser::ParagraphContext *ctx) = 0;

  virtual void enterText(potatoParser::TextContext *ctx) = 0;
  virtual void exitText(potatoParser::TextContext *ctx) = 0;

  virtual void enterOneline_text(potatoParser::Oneline_textContext *ctx) = 0;
  virtual void exitOneline_text(potatoParser::Oneline_textContext *ctx) = 0;

  virtual void enterText_colon(potatoParser::Text_colonContext *ctx) = 0;
  virtual void exitText_colon(potatoParser::Text_colonContext *ctx) = 0;


};

