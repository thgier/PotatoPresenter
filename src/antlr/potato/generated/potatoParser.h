
// Generated from potato.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  potatoParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    SPECIAL_CHARACTER = 8, WORD = 9, TEXT_BRACKET = 10
  };

  enum {
    RulePotato = 0, RuleBox = 1, RuleParagraph = 2, RuleText = 3, RuleMultiline_text = 4, 
    RuleOneline_text = 5, RuleFirst_word = 6, RuleEvery_letter_word = 7, 
    RuleProperty_list = 8, RuleProperty_entry = 9, RuleProperty = 10, RuleValue = 11, 
    RuleCommand = 12, RuleText_in_bracket = 13, RuleWs = 14
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
  class ParagraphContext;
  class TextContext;
  class Multiline_textContext;
  class Oneline_textContext;
  class First_wordContext;
  class Every_letter_wordContext;
  class Property_listContext;
  class Property_entryContext;
  class PropertyContext;
  class ValueContext;
  class CommandContext;
  class Text_in_bracketContext;
  class WsContext; 

  class  PotatoContext : public antlr4::ParserRuleContext {
  public:
    PotatoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    antlr4::tree::TerminalNode *EOF();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    Property_listContext *property_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BoxContext* box();

  class  ParagraphContext : public antlr4::ParserRuleContext {
  public:
    ParagraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Text_in_bracketContext *text_in_bracket();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);
    TextContext *text();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParagraphContext* paragraph();

  class  TextContext : public antlr4::ParserRuleContext {
  public:
    TextContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Oneline_textContext *oneline_text();
    Multiline_textContext *multiline_text();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextContext* text();

  class  Multiline_textContext : public antlr4::ParserRuleContext {
  public:
    Multiline_textContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Oneline_textContext *> oneline_text();
    Oneline_textContext* oneline_text(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Multiline_textContext* multiline_text();

  class  Oneline_textContext : public antlr4::ParserRuleContext {
  public:
    Oneline_textContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    First_wordContext *first_word();
    std::vector<Every_letter_wordContext *> every_letter_word();
    Every_letter_wordContext* every_letter_word(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Oneline_textContext* oneline_text();

  class  First_wordContext : public antlr4::ParserRuleContext {
  public:
    First_wordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WORD();
    antlr4::tree::TerminalNode *SPECIAL_CHARACTER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  First_wordContext* first_word();

  class  Every_letter_wordContext : public antlr4::ParserRuleContext {
  public:
    Every_letter_wordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    First_wordContext *first_word();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Every_letter_wordContext* every_letter_word();

  class  Property_listContext : public antlr4::ParserRuleContext {
  public:
    Property_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Property_entryContext *> property_entry();
    Property_entryContext* property_entry(size_t i);
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Property_listContext* property_list();

  class  Property_entryContext : public antlr4::ParserRuleContext {
  public:
    Property_entryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyContext *property();
    ValueContext *value();
    std::vector<WsContext *> ws();
    WsContext* ws(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Property_entryContext* property_entry();

  class  PropertyContext : public antlr4::ParserRuleContext {
  public:
    PropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WORD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyContext* property();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> WORD();
    antlr4::tree::TerminalNode* WORD(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ValueContext* value();

  class  CommandContext : public antlr4::ParserRuleContext {
  public:
    CommandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WORD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CommandContext* command();

  class  Text_in_bracketContext : public antlr4::ParserRuleContext {
  public:
    Text_in_bracketContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEXT_BRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Text_in_bracketContext* text_in_bracket();

  class  WsContext : public antlr4::ParserRuleContext {
  public:
    WsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WsContext* ws();


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

