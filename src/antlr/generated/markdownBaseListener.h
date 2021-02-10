
// Generated from markdown.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "markdownListener.h"


/**
 * This class provides an empty implementation of markdownListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  markdownBaseListener : public markdownListener {
public:

  virtual void enterMarkdown(markdownParser::MarkdownContext * /*ctx*/) override { }
  virtual void exitMarkdown(markdownParser::MarkdownContext * /*ctx*/) override { }

  virtual void enterList(markdownParser::ListContext * /*ctx*/) override { }
  virtual void exitList(markdownParser::ListContext * /*ctx*/) override { }

  virtual void enterItem_second(markdownParser::Item_secondContext * /*ctx*/) override { }
  virtual void exitItem_second(markdownParser::Item_secondContext * /*ctx*/) override { }

  virtual void enterItem(markdownParser::ItemContext * /*ctx*/) override { }
  virtual void exitItem(markdownParser::ItemContext * /*ctx*/) override { }

  virtual void enterItemize(markdownParser::ItemizeContext * /*ctx*/) override { }
  virtual void exitItemize(markdownParser::ItemizeContext * /*ctx*/) override { }

  virtual void enterEnumeration(markdownParser::EnumerationContext * /*ctx*/) override { }
  virtual void exitEnumeration(markdownParser::EnumerationContext * /*ctx*/) override { }

  virtual void enterEnum_item(markdownParser::Enum_itemContext * /*ctx*/) override { }
  virtual void exitEnum_item(markdownParser::Enum_itemContext * /*ctx*/) override { }

  virtual void enterEnum_item_second(markdownParser::Enum_item_secondContext * /*ctx*/) override { }
  virtual void exitEnum_item_second(markdownParser::Enum_item_secondContext * /*ctx*/) override { }

  virtual void enterParagraph(markdownParser::ParagraphContext * /*ctx*/) override { }
  virtual void exitParagraph(markdownParser::ParagraphContext * /*ctx*/) override { }

  virtual void enterText_decorated(markdownParser::Text_decoratedContext * /*ctx*/) override { }
  virtual void exitText_decorated(markdownParser::Text_decoratedContext * /*ctx*/) override { }

  virtual void enterText_bold(markdownParser::Text_boldContext * /*ctx*/) override { }
  virtual void exitText_bold(markdownParser::Text_boldContext * /*ctx*/) override { }

  virtual void enterText_italic(markdownParser::Text_italicContext * /*ctx*/) override { }
  virtual void exitText_italic(markdownParser::Text_italicContext * /*ctx*/) override { }

  virtual void enterText_plain(markdownParser::Text_plainContext * /*ctx*/) override { }
  virtual void exitText_plain(markdownParser::Text_plainContext * /*ctx*/) override { }

  virtual void enterLatex(markdownParser::LatexContext * /*ctx*/) override { }
  virtual void exitLatex(markdownParser::LatexContext * /*ctx*/) override { }

  virtual void enterLatex_next_line(markdownParser::Latex_next_lineContext * /*ctx*/) override { }
  virtual void exitLatex_next_line(markdownParser::Latex_next_lineContext * /*ctx*/) override { }

  virtual void enterNew_line(markdownParser::New_lineContext * /*ctx*/) override { }
  virtual void exitNew_line(markdownParser::New_lineContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

