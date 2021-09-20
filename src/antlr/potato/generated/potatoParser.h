
// Generated from potato.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  potatoParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, BACKSLASH = 7, 
    BACKSLASH_CURLED_BRACKET_OPEN = 8, BACKSLASH_CURLED_BRACKET_CLOSE = 9, 
    NEWLINE = 10, SPACE = 11, TEXT = 12
  };

  enum {
    RulePotato = 0, RuleBox = 1, RuleCommand = 2, RuleProperty_entry = 3, 
    RuleProberty = 4, RuleValue = 5, RuleParagraph = 6, RuleParagraph_without_bracket = 7, 
    RuleParagraph_bracket = 8, RuleText = 9, RuleOneline_text_first = 10, 
    RuleOneline_text = 11, RuleText_in_bracket = 12, RuleText_sign = 13
  };

  explicit potatoParser(antlr4::TokenStream *input);
  ~potatoParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class PotatoContext;
  class BoxContext;
  class CommandContext;
  class Property_entryContext;
  class ProbertyContext;
  class ValueContext;
  class ParagraphContext;
  class Paragraph_without_bracketContext;
  class Paragraph_bracketContext;
  class TextContext;
  class Oneline_text_firstContext;
  class Oneline_textContext;
  class Text_in_bracketContext;
  class Text_signContext; 

  class  PotatoContext : public antlr4::ParserRuleContext {
  public:
    PotatoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<BoxContext *> box();
    BoxContext* box(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PotatoContext* potato();

  class  BoxContext : public antlr4::ParserRuleContext {
  public:
    BoxContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CommandContext *command();
    ParagraphContext *paragraph();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BoxContext* box();

  class  CommandContext : public antlr4::ParserRuleContext {
  public:
    CommandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BACKSLASH();
    antlr4::tree::TerminalNode *TEXT();
    std::vector<Property_entryContext *> property_entry();
    Property_entryContext* property_entry(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CommandContext* command();

  class  Property_entryContext : public antlr4::ParserRuleContext {
  public:
    Property_entryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProbertyContext *proberty();
    ValueContext *value();
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Property_entryContext* property_entry();

  class  ProbertyContext : public antlr4::ParserRuleContext {
  public:
    ProbertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TEXT();
    antlr4::tree::TerminalNode* TEXT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProbertyContext* proberty();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TEXT();
    antlr4::tree::TerminalNode* TEXT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ValueContext* value();

  class  ParagraphContext : public antlr4::ParserRuleContext {
  public:
    ParagraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Paragraph_bracketContext *paragraph_bracket();
    Paragraph_without_bracketContext *paragraph_without_bracket();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParagraphContext* paragraph();

  class  Paragraph_without_bracketContext : public antlr4::ParserRuleContext {
  public:
    Paragraph_without_bracketContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *EOF();
    TextContext *text();
    antlr4::tree::TerminalNode *SPACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Paragraph_without_bracketContext* paragraph_without_bracket();

  class  Paragraph_bracketContext : public antlr4::ParserRuleContext {
  public:
    Paragraph_bracketContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BACKSLASH_CURLED_BRACKET_OPEN();
    Text_in_bracketContext *text_in_bracket();
    antlr4::tree::TerminalNode *BACKSLASH_CURLED_BRACKET_CLOSE();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Paragraph_bracketContext* paragraph_bracket();

  class  TextContext : public antlr4::ParserRuleContext {
  public:
    TextContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Oneline_text_firstContext *oneline_text_first();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<Oneline_textContext *> oneline_text();
    Oneline_textContext* oneline_text(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextContext* text();

  class  Oneline_text_firstContext : public antlr4::ParserRuleContext {
  public:
    Oneline_text_firstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_signContext *> text_sign();
    Text_signContext* text_sign(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BACKSLASH();
    antlr4::tree::TerminalNode* BACKSLASH(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Oneline_text_firstContext* oneline_text_first();

  class  Oneline_textContext : public antlr4::ParserRuleContext {
  public:
    Oneline_textContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_signContext *> text_sign();
    Text_signContext* text_sign(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BACKSLASH();
    antlr4::tree::TerminalNode* BACKSLASH(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Oneline_textContext* oneline_text();

  class  Text_in_bracketContext : public antlr4::ParserRuleContext {
  public:
    Text_in_bracketContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Text_signContext *> text_sign();
    Text_signContext* text_sign(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BACKSLASH();
    antlr4::tree::TerminalNode* BACKSLASH(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_in_bracketContext* text_in_bracket();

  class  Text_signContext : public antlr4::ParserRuleContext {
  public:
    Text_signContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TEXT();
    antlr4::tree::TerminalNode* TEXT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_signContext* text_sign();


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

