
// Generated from markdown.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "markdownParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by markdownParser.
 */
class  markdownListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterMarkdown(markdownParser::MarkdownContext *ctx) = 0;
  virtual void exitMarkdown(markdownParser::MarkdownContext *ctx) = 0;

  virtual void enterList(markdownParser::ListContext *ctx) = 0;
  virtual void exitList(markdownParser::ListContext *ctx) = 0;

  virtual void enterItemization(markdownParser::ItemizationContext *ctx) = 0;
  virtual void exitItemization(markdownParser::ItemizationContext *ctx) = 0;

  virtual void enterItem_second(markdownParser::Item_secondContext *ctx) = 0;
  virtual void exitItem_second(markdownParser::Item_secondContext *ctx) = 0;

  virtual void enterItem(markdownParser::ItemContext *ctx) = 0;
  virtual void exitItem(markdownParser::ItemContext *ctx) = 0;

  virtual void enterEnum_item_second(markdownParser::Enum_item_secondContext *ctx) = 0;
  virtual void exitEnum_item_second(markdownParser::Enum_item_secondContext *ctx) = 0;

  virtual void enterParagraph(markdownParser::ParagraphContext *ctx) = 0;
  virtual void exitParagraph(markdownParser::ParagraphContext *ctx) = 0;

  virtual void enterText_decorated(markdownParser::Text_decoratedContext *ctx) = 0;
  virtual void exitText_decorated(markdownParser::Text_decoratedContext *ctx) = 0;

  virtual void enterText_bold(markdownParser::Text_boldContext *ctx) = 0;
  virtual void exitText_bold(markdownParser::Text_boldContext *ctx) = 0;

  virtual void enterText_marked(markdownParser::Text_markedContext *ctx) = 0;
  virtual void exitText_marked(markdownParser::Text_markedContext *ctx) = 0;

  virtual void enterText_italic(markdownParser::Text_italicContext *ctx) = 0;
  virtual void exitText_italic(markdownParser::Text_italicContext *ctx) = 0;

  virtual void enterLatex(markdownParser::LatexContext *ctx) = 0;
  virtual void exitLatex(markdownParser::LatexContext *ctx) = 0;

  virtual void enterLatex_next_line(markdownParser::Latex_next_lineContext *ctx) = 0;
  virtual void exitLatex_next_line(markdownParser::Latex_next_lineContext *ctx) = 0;

  virtual void enterText_plain(markdownParser::Text_plainContext *ctx) = 0;
  virtual void exitText_plain(markdownParser::Text_plainContext *ctx) = 0;


};

