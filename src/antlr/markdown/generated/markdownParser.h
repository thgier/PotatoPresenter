
// Generated from markdown.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  markdownParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    ITEM_SECOND_INTRO = 8, ENUM_SECOND_INTRO = 9, UNDERSCORE = 10, STAR = 11, 
    INT = 12, TEXT = 13
  };

  enum {
    RuleMarkdown = 0, RuleList = 1, RuleItemization = 2, RuleItem_second = 3, 
    RuleItem = 4, RuleEnum_item_second = 5, RuleParagraph = 6, RuleText_decorated = 7, 
    RuleText_bold = 8, RuleText_marked = 9, RuleText_italic = 10, RuleLatex = 11, 
    RuleLatex_next_line = 12, RuleText_plain = 13
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
  class ItemizationContext;
  class Item_secondContext;
  class ItemContext;
  class Enum_item_secondContext;
  class ParagraphContext;
  class Text_decoratedContext;
  class Text_boldContext;
  class Text_markedContext;
  class Text_italicContext;
  class LatexContext;
  class Latex_next_lineContext;
  class Text_plainContext; 

  class  MarkdownContext : public antlr4::ParserRuleContext {
  public:
    MarkdownContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ParagraphContext *> paragraph();
    ParagraphContext* paragraph(size_t i);
    std::vector<ListContext *> list();
    ListContext* list(size_t i);
    std::vector<Latex_next_lineContext *> latex_next_line();
    Latex_next_lineContext* latex_next_line(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MarkdownContext* markdown();

  class  ListContext : public antlr4::ParserRuleContext {
  public:
    ListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ItemizationContext *itemization();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ListContext* list();

  class  ItemizationContext : public antlr4::ParserRuleContext {
  public:
    ItemizationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ItemContext *> item();
    ItemContext* item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ItemizationContext* itemization();

  class  Item_secondContext : public antlr4::ParserRuleContext {
  public:
    Item_secondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ITEM_SECOND_INTRO();
    ParagraphContext *paragraph();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_secondContext* item_second();

  class  ItemContext : public antlr4::ParserRuleContext {
  public:
    ItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    ParagraphContext *paragraph();
    std::vector<Enum_item_secondContext *> enum_item_second();
    Enum_item_secondContext* enum_item_second(size_t i);
    std::vector<Item_secondContext *> item_second();
    Item_secondContext* item_second(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ItemContext* item();

  class  Enum_item_secondContext : public antlr4::ParserRuleContext {
  public:
    Enum_item_secondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM_SECOND_INTRO();
    ParagraphContext *paragraph();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Enum_item_secondContext* enum_item_second();

  class  ParagraphContext : public antlr4::ParserRuleContext {
  public:
    ParagraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_decoratedContext *> text_decorated();
    Text_decoratedContext* text_decorated(size_t i);
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<LatexContext *> latex();
    LatexContext* latex(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNDERSCORE();
    antlr4::tree::TerminalNode* UNDERSCORE(size_t i);

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
    Text_markedContext *text_marked();

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
    std::vector<Text_italicContext *> text_italic();
    Text_italicContext* text_italic(size_t i);
    std::vector<Text_markedContext *> text_marked();
    Text_markedContext* text_marked(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_boldContext* text_bold();

  class  Text_markedContext : public antlr4::ParserRuleContext {
  public:
    Text_markedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_markedContext* text_marked();

  class  Text_italicContext : public antlr4::ParserRuleContext {
  public:
    Text_italicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<Text_boldContext *> text_bold();
    Text_boldContext* text_bold(size_t i);
    std::vector<Text_markedContext *> text_marked();
    Text_markedContext* text_marked(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_italicContext* text_italic();

  class  LatexContext : public antlr4::ParserRuleContext {
  public:
    LatexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNDERSCORE();
    antlr4::tree::TerminalNode* UNDERSCORE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LatexContext* latex();

  class  Latex_next_lineContext : public antlr4::ParserRuleContext {
  public:
    Latex_next_lineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_plainContext *> text_plain();
    Text_plainContext* text_plain(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNDERSCORE();
    antlr4::tree::TerminalNode* UNDERSCORE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Latex_next_lineContext* latex_next_line();

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

