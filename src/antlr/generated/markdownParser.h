
// Generated from markdown.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"




class  markdownParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, INT = 12, TEXT = 13
  };

  enum {
    RuleMarkdown = 0, RuleList = 1, RuleItem_second = 2, RuleItem = 3, RuleItemize = 4, 
    RuleEnumeration = 5, RuleEnum_item = 6, RuleEnum_item_second = 7, RuleParagraph = 8, 
    RuleText_decorated = 9, RuleText_bold = 10, RuleText_italic = 11, RuleText_plain = 12, 
    RuleLatex = 13, RuleLatex_next_line = 14, RuleNew_line = 15
  };

  explicit markdownParser(antlr4::TokenStream *input);
  ~markdownParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class MarkdownContext;
  class ListContext;
  class Item_secondContext;
  class ItemContext;
  class ItemizeContext;
  class EnumerationContext;
  class Enum_itemContext;
  class Enum_item_secondContext;
  class ParagraphContext;
  class Text_decoratedContext;
  class Text_boldContext;
  class Text_italicContext;
  class Text_plainContext;
  class LatexContext;
  class Latex_next_lineContext;
  class New_lineContext; 

  class  MarkdownContext : public antlr4::ParserRuleContext {
  public:
    MarkdownContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ListContext *> list();
    ListContext* list(size_t i);
    std::vector<ParagraphContext *> paragraph();
    ParagraphContext* paragraph(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MarkdownContext* markdown();

  class  ListContext : public antlr4::ParserRuleContext {
  public:
    ListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ItemizeContext *itemize();
    EnumerationContext *enumeration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ListContext* list();

  class  Item_secondContext : public antlr4::ParserRuleContext {
  public:
    Item_secondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParagraphContext *paragraph();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_secondContext* item_second();

  class  ItemContext : public antlr4::ParserRuleContext {
  public:
    ItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Item_secondContext *> item_second();
    Item_secondContext* item_second(size_t i);
    ParagraphContext *paragraph();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ItemContext* item();

  class  ItemizeContext : public antlr4::ParserRuleContext {
  public:
    ItemizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ItemContext *> item();
    ItemContext* item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ItemizeContext* itemize();

  class  EnumerationContext : public antlr4::ParserRuleContext {
  public:
    EnumerationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Enum_itemContext *> enum_item();
    Enum_itemContext* enum_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumerationContext* enumeration();

  class  Enum_itemContext : public antlr4::ParserRuleContext {
  public:
    Enum_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    ParagraphContext *paragraph();
    std::vector<Enum_item_secondContext *> enum_item_second();
    Enum_item_secondContext* enum_item_second(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Enum_itemContext* enum_item();

  class  Enum_item_secondContext : public antlr4::ParserRuleContext {
  public:
    Enum_item_secondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    ParagraphContext *paragraph();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Enum_item_secondContext* enum_item_second();

  class  ParagraphContext : public antlr4::ParserRuleContext {
  public:
    ParagraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    New_lineContext *new_line();
    antlr4::tree::TerminalNode *EOF();
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<Text_decoratedContext *> text_decorated();
    Text_decoratedContext* text_decorated(size_t i);
    std::vector<LatexContext *> latex();
    LatexContext* latex(size_t i);
    std::vector<Latex_next_lineContext *> latex_next_line();
    Latex_next_lineContext* latex_next_line(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParagraphContext* paragraph();

  class  Text_decoratedContext : public antlr4::ParserRuleContext {
  public:
    Text_decoratedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Text_boldContext *text_bold();
    Text_italicContext *text_italic();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_decoratedContext* text_decorated();

  class  Text_boldContext : public antlr4::ParserRuleContext {
  public:
    Text_boldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<Text_decoratedContext *> text_decorated();
    Text_decoratedContext* text_decorated(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_boldContext* text_bold();

  class  Text_italicContext : public antlr4::ParserRuleContext {
  public:
    Text_italicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<Text_decoratedContext *> text_decorated();
    Text_decoratedContext* text_decorated(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_italicContext* text_italic();

  class  Text_plainContext : public antlr4::ParserRuleContext {
  public:
    Text_plainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TEXT();
    antlr4::tree::TerminalNode* TEXT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> INT();
    antlr4::tree::TerminalNode* INT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_plainContext* text_plain();

  class  LatexContext : public antlr4::ParserRuleContext {
  public:
    LatexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Text_plainContext *text_plain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LatexContext* latex();

  class  Latex_next_lineContext : public antlr4::ParserRuleContext {
  public:
    Latex_next_lineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<New_lineContext *> new_line();
    New_lineContext* new_line(size_t i);
    Text_plainContext *text_plain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Latex_next_lineContext* latex_next_line();

  class  New_lineContext : public antlr4::ParserRuleContext {
  public:
    New_lineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  New_lineContext* new_line();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

