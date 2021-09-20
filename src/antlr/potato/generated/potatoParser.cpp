
// Generated from potato.g4 by ANTLR 4.9.2


#include "potatoListener.h"

#include "potatoParser.h"


using namespace antlrcpp;
using namespace antlr4;

potatoParser::potatoParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

potatoParser::~potatoParser() {
  delete _interpreter;
}

std::string potatoParser::getGrammarFileName() const {
  return "potato.g4";
}

const std::vector<std::string>& potatoParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& potatoParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- PotatoContext ------------------------------------------------------------------

potatoParser::PotatoContext::PotatoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::PotatoContext::NEWLINE() {
  return getToken(potatoParser::NEWLINE, 0);
}

std::vector<potatoParser::BoxContext *> potatoParser::PotatoContext::box() {
  return getRuleContexts<potatoParser::BoxContext>();
}

potatoParser::BoxContext* potatoParser::PotatoContext::box(size_t i) {
  return getRuleContext<potatoParser::BoxContext>(i);
}


size_t potatoParser::PotatoContext::getRuleIndex() const {
  return potatoParser::RulePotato;
}

void potatoParser::PotatoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPotato(this);
}

void potatoParser::PotatoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPotato(this);
}

potatoParser::PotatoContext* potatoParser::potato() {
  PotatoContext *_localctx = _tracker.createInstance<PotatoContext>(_ctx, getState());
  enterRule(_localctx, 0, potatoParser::RulePotato);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::NEWLINE) {
      setState(28);
      match(potatoParser::NEWLINE);
    }
    setState(34);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == potatoParser::BACKSLASH) {
      setState(31);
      box();
      setState(36);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoxContext ------------------------------------------------------------------

potatoParser::BoxContext::BoxContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

potatoParser::CommandContext* potatoParser::BoxContext::command() {
  return getRuleContext<potatoParser::CommandContext>(0);
}

potatoParser::ParagraphContext* potatoParser::BoxContext::paragraph() {
  return getRuleContext<potatoParser::ParagraphContext>(0);
}


size_t potatoParser::BoxContext::getRuleIndex() const {
  return potatoParser::RuleBox;
}

void potatoParser::BoxContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBox(this);
}

void potatoParser::BoxContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBox(this);
}

potatoParser::BoxContext* potatoParser::box() {
  BoxContext *_localctx = _tracker.createInstance<BoxContext>(_ctx, getState());
  enterRule(_localctx, 2, potatoParser::RuleBox);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    command();
    setState(38);
    paragraph();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommandContext ------------------------------------------------------------------

potatoParser::CommandContext::CommandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::CommandContext::BACKSLASH() {
  return getToken(potatoParser::BACKSLASH, 0);
}

tree::TerminalNode* potatoParser::CommandContext::TEXT() {
  return getToken(potatoParser::TEXT, 0);
}

std::vector<potatoParser::Property_entryContext *> potatoParser::CommandContext::property_entry() {
  return getRuleContexts<potatoParser::Property_entryContext>();
}

potatoParser::Property_entryContext* potatoParser::CommandContext::property_entry(size_t i) {
  return getRuleContext<potatoParser::Property_entryContext>(i);
}

std::vector<tree::TerminalNode *> potatoParser::CommandContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::CommandContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}


size_t potatoParser::CommandContext::getRuleIndex() const {
  return potatoParser::RuleCommand;
}

void potatoParser::CommandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCommand(this);
}

void potatoParser::CommandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCommand(this);
}

potatoParser::CommandContext* potatoParser::command() {
  CommandContext *_localctx = _tracker.createInstance<CommandContext>(_ctx, getState());
  enterRule(_localctx, 4, potatoParser::RuleCommand);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    match(potatoParser::BACKSLASH);
    setState(41);
    match(potatoParser::TEXT);
    setState(56);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(42);
      match(potatoParser::T__0);
      setState(43);
      property_entry();
      setState(51);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == potatoParser::T__1) {
        setState(44);
        match(potatoParser::T__1);
        setState(46);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          setState(45);
          match(potatoParser::SPACE);
          break;
        }

        default:
          break;
        }
        setState(48);
        property_entry();
        setState(53);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(54);
      match(potatoParser::T__2);
      break;
    }

    default:
      break;
    }
    setState(59);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(58);
      match(potatoParser::SPACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_entryContext ------------------------------------------------------------------

potatoParser::Property_entryContext::Property_entryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

potatoParser::ProbertyContext* potatoParser::Property_entryContext::proberty() {
  return getRuleContext<potatoParser::ProbertyContext>(0);
}

potatoParser::ValueContext* potatoParser::Property_entryContext::value() {
  return getRuleContext<potatoParser::ValueContext>(0);
}

std::vector<tree::TerminalNode *> potatoParser::Property_entryContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::Property_entryContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}


size_t potatoParser::Property_entryContext::getRuleIndex() const {
  return potatoParser::RuleProperty_entry;
}

void potatoParser::Property_entryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_entry(this);
}

void potatoParser::Property_entryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_entry(this);
}

potatoParser::Property_entryContext* potatoParser::property_entry() {
  Property_entryContext *_localctx = _tracker.createInstance<Property_entryContext>(_ctx, getState());
  enterRule(_localctx, 6, potatoParser::RuleProperty_entry);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    proberty();
    setState(63);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::SPACE) {
      setState(62);
      match(potatoParser::SPACE);
    }
    setState(65);
    match(potatoParser::T__3);
    setState(67);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(66);
      match(potatoParser::SPACE);
      break;
    }

    default:
      break;
    }
    setState(69);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProbertyContext ------------------------------------------------------------------

potatoParser::ProbertyContext::ProbertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> potatoParser::ProbertyContext::TEXT() {
  return getTokens(potatoParser::TEXT);
}

tree::TerminalNode* potatoParser::ProbertyContext::TEXT(size_t i) {
  return getToken(potatoParser::TEXT, i);
}

std::vector<tree::TerminalNode *> potatoParser::ProbertyContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::ProbertyContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}


size_t potatoParser::ProbertyContext::getRuleIndex() const {
  return potatoParser::RuleProberty;
}

void potatoParser::ProbertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProberty(this);
}

void potatoParser::ProbertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProberty(this);
}

potatoParser::ProbertyContext* potatoParser::proberty() {
  ProbertyContext *_localctx = _tracker.createInstance<ProbertyContext>(_ctx, getState());
  enterRule(_localctx, 8, potatoParser::RuleProberty);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(72); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(71);
              _la = _input->LA(1);
              if (!(_la == potatoParser::SPACE

              || _la == potatoParser::TEXT)) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(74); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

potatoParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> potatoParser::ValueContext::TEXT() {
  return getTokens(potatoParser::TEXT);
}

tree::TerminalNode* potatoParser::ValueContext::TEXT(size_t i) {
  return getToken(potatoParser::TEXT, i);
}

std::vector<tree::TerminalNode *> potatoParser::ValueContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::ValueContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}


size_t potatoParser::ValueContext::getRuleIndex() const {
  return potatoParser::RuleValue;
}

void potatoParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void potatoParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

potatoParser::ValueContext* potatoParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 10, potatoParser::RuleValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(76);
      _la = _input->LA(1);
      if (!(_la == potatoParser::SPACE

      || _la == potatoParser::TEXT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(79); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == potatoParser::SPACE

    || _la == potatoParser::TEXT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParagraphContext ------------------------------------------------------------------

potatoParser::ParagraphContext::ParagraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

potatoParser::Paragraph_bracketContext* potatoParser::ParagraphContext::paragraph_bracket() {
  return getRuleContext<potatoParser::Paragraph_bracketContext>(0);
}

potatoParser::Paragraph_without_bracketContext* potatoParser::ParagraphContext::paragraph_without_bracket() {
  return getRuleContext<potatoParser::Paragraph_without_bracketContext>(0);
}


size_t potatoParser::ParagraphContext::getRuleIndex() const {
  return potatoParser::RuleParagraph;
}

void potatoParser::ParagraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParagraph(this);
}

void potatoParser::ParagraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParagraph(this);
}

potatoParser::ParagraphContext* potatoParser::paragraph() {
  ParagraphContext *_localctx = _tracker.createInstance<ParagraphContext>(_ctx, getState());
  enterRule(_localctx, 12, potatoParser::RuleParagraph);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(83);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(81);
      paragraph_bracket();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(82);
      paragraph_without_bracket();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Paragraph_without_bracketContext ------------------------------------------------------------------

potatoParser::Paragraph_without_bracketContext::Paragraph_without_bracketContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> potatoParser::Paragraph_without_bracketContext::NEWLINE() {
  return getTokens(potatoParser::NEWLINE);
}

tree::TerminalNode* potatoParser::Paragraph_without_bracketContext::NEWLINE(size_t i) {
  return getToken(potatoParser::NEWLINE, i);
}

tree::TerminalNode* potatoParser::Paragraph_without_bracketContext::EOF() {
  return getToken(potatoParser::EOF, 0);
}

potatoParser::TextContext* potatoParser::Paragraph_without_bracketContext::text() {
  return getRuleContext<potatoParser::TextContext>(0);
}

tree::TerminalNode* potatoParser::Paragraph_without_bracketContext::SPACE() {
  return getToken(potatoParser::SPACE, 0);
}


size_t potatoParser::Paragraph_without_bracketContext::getRuleIndex() const {
  return potatoParser::RuleParagraph_without_bracket;
}

void potatoParser::Paragraph_without_bracketContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParagraph_without_bracket(this);
}

void potatoParser::Paragraph_without_bracketContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParagraph_without_bracket(this);
}

potatoParser::Paragraph_without_bracketContext* potatoParser::paragraph_without_bracket() {
  Paragraph_without_bracketContext *_localctx = _tracker.createInstance<Paragraph_without_bracketContext>(_ctx, getState());
  enterRule(_localctx, 14, potatoParser::RuleParagraph_without_bracket);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(86);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
      case 1: {
        setState(85);
        match(potatoParser::SPACE);
        break;
      }

      default:
        break;
      }
      setState(89);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == potatoParser::NEWLINE) {
        setState(88);
        match(potatoParser::NEWLINE);
      }
      setState(91);
      text();
      break;
    }

    default:
      break;
    }
    setState(99);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(94);
      match(potatoParser::NEWLINE);
      break;
    }

    case 2: {
      setState(96);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == potatoParser::NEWLINE) {
        setState(95);
        match(potatoParser::NEWLINE);
      }
      setState(98);
      match(potatoParser::EOF);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Paragraph_bracketContext ------------------------------------------------------------------

potatoParser::Paragraph_bracketContext::Paragraph_bracketContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::Paragraph_bracketContext::BACKSLASH_CURLED_BRACKET_OPEN() {
  return getToken(potatoParser::BACKSLASH_CURLED_BRACKET_OPEN, 0);
}

potatoParser::Text_in_bracketContext* potatoParser::Paragraph_bracketContext::text_in_bracket() {
  return getRuleContext<potatoParser::Text_in_bracketContext>(0);
}

tree::TerminalNode* potatoParser::Paragraph_bracketContext::BACKSLASH_CURLED_BRACKET_CLOSE() {
  return getToken(potatoParser::BACKSLASH_CURLED_BRACKET_CLOSE, 0);
}

std::vector<tree::TerminalNode *> potatoParser::Paragraph_bracketContext::NEWLINE() {
  return getTokens(potatoParser::NEWLINE);
}

tree::TerminalNode* potatoParser::Paragraph_bracketContext::NEWLINE(size_t i) {
  return getToken(potatoParser::NEWLINE, i);
}

tree::TerminalNode* potatoParser::Paragraph_bracketContext::EOF() {
  return getToken(potatoParser::EOF, 0);
}

std::vector<tree::TerminalNode *> potatoParser::Paragraph_bracketContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::Paragraph_bracketContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}


size_t potatoParser::Paragraph_bracketContext::getRuleIndex() const {
  return potatoParser::RuleParagraph_bracket;
}

void potatoParser::Paragraph_bracketContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParagraph_bracket(this);
}

void potatoParser::Paragraph_bracketContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParagraph_bracket(this);
}

potatoParser::Paragraph_bracketContext* potatoParser::paragraph_bracket() {
  Paragraph_bracketContext *_localctx = _tracker.createInstance<Paragraph_bracketContext>(_ctx, getState());
  enterRule(_localctx, 16, potatoParser::RuleParagraph_bracket);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::SPACE) {
      setState(101);
      match(potatoParser::SPACE);
    }
    setState(105);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::NEWLINE) {
      setState(104);
      match(potatoParser::NEWLINE);
    }
    setState(107);
    match(potatoParser::BACKSLASH_CURLED_BRACKET_OPEN);
    setState(109);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(108);
      match(potatoParser::SPACE);
      break;
    }

    default:
      break;
    }
    setState(112);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(111);
      match(potatoParser::NEWLINE);
      break;
    }

    default:
      break;
    }
    setState(114);
    text_in_bracket();
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::SPACE) {
      setState(115);
      match(potatoParser::SPACE);
    }
    setState(119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::NEWLINE) {
      setState(118);
      match(potatoParser::NEWLINE);
    }
    setState(121);
    match(potatoParser::BACKSLASH_CURLED_BRACKET_CLOSE);
    setState(127);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(122);
      match(potatoParser::NEWLINE);
      break;
    }

    case 2: {
      setState(124);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == potatoParser::NEWLINE) {
        setState(123);
        match(potatoParser::NEWLINE);
      }
      setState(126);
      match(potatoParser::EOF);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextContext ------------------------------------------------------------------

potatoParser::TextContext::TextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

potatoParser::Oneline_text_firstContext* potatoParser::TextContext::oneline_text_first() {
  return getRuleContext<potatoParser::Oneline_text_firstContext>(0);
}

std::vector<tree::TerminalNode *> potatoParser::TextContext::NEWLINE() {
  return getTokens(potatoParser::NEWLINE);
}

tree::TerminalNode* potatoParser::TextContext::NEWLINE(size_t i) {
  return getToken(potatoParser::NEWLINE, i);
}

std::vector<potatoParser::Oneline_textContext *> potatoParser::TextContext::oneline_text() {
  return getRuleContexts<potatoParser::Oneline_textContext>();
}

potatoParser::Oneline_textContext* potatoParser::TextContext::oneline_text(size_t i) {
  return getRuleContext<potatoParser::Oneline_textContext>(i);
}


size_t potatoParser::TextContext::getRuleIndex() const {
  return potatoParser::RuleText;
}

void potatoParser::TextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText(this);
}

void potatoParser::TextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText(this);
}

potatoParser::TextContext* potatoParser::text() {
  TextContext *_localctx = _tracker.createInstance<TextContext>(_ctx, getState());
  enterRule(_localctx, 18, potatoParser::RuleText);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(129);
    oneline_text_first();
    setState(134);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(130);
        match(potatoParser::NEWLINE);
        setState(131);
        oneline_text(); 
      }
      setState(136);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Oneline_text_firstContext ------------------------------------------------------------------

potatoParser::Oneline_text_firstContext::Oneline_text_firstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<potatoParser::Text_signContext *> potatoParser::Oneline_text_firstContext::text_sign() {
  return getRuleContexts<potatoParser::Text_signContext>();
}

potatoParser::Text_signContext* potatoParser::Oneline_text_firstContext::text_sign(size_t i) {
  return getRuleContext<potatoParser::Text_signContext>(i);
}

std::vector<tree::TerminalNode *> potatoParser::Oneline_text_firstContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::Oneline_text_firstContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}

std::vector<tree::TerminalNode *> potatoParser::Oneline_text_firstContext::BACKSLASH() {
  return getTokens(potatoParser::BACKSLASH);
}

tree::TerminalNode* potatoParser::Oneline_text_firstContext::BACKSLASH(size_t i) {
  return getToken(potatoParser::BACKSLASH, i);
}


size_t potatoParser::Oneline_text_firstContext::getRuleIndex() const {
  return potatoParser::RuleOneline_text_first;
}

void potatoParser::Oneline_text_firstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOneline_text_first(this);
}

void potatoParser::Oneline_text_firstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOneline_text_first(this);
}

potatoParser::Oneline_text_firstContext* potatoParser::oneline_text_first() {
  Oneline_text_firstContext *_localctx = _tracker.createInstance<Oneline_text_firstContext>(_ctx, getState());
  enterRule(_localctx, 20, potatoParser::RuleOneline_text_first);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(141); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(141);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case potatoParser::T__0:
                case potatoParser::T__1:
                case potatoParser::T__2:
                case potatoParser::T__3:
                case potatoParser::TEXT: {
                  setState(137);
                  text_sign();
                  break;
                }

                case potatoParser::T__4: {
                  setState(138);
                  match(potatoParser::T__4);
                  break;
                }

                case potatoParser::T__5: {
                  setState(139);
                  match(potatoParser::T__5);
                  break;
                }

                case potatoParser::SPACE: {
                  setState(140);
                  match(potatoParser::SPACE);
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(143); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(152);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << potatoParser::T__0)
      | (1ULL << potatoParser::T__1)
      | (1ULL << potatoParser::T__2)
      | (1ULL << potatoParser::T__3)
      | (1ULL << potatoParser::T__4)
      | (1ULL << potatoParser::T__5)
      | (1ULL << potatoParser::BACKSLASH)
      | (1ULL << potatoParser::SPACE)
      | (1ULL << potatoParser::TEXT))) != 0)) {
      setState(150);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case potatoParser::T__0:
        case potatoParser::T__1:
        case potatoParser::T__2:
        case potatoParser::T__3:
        case potatoParser::TEXT: {
          setState(145);
          text_sign();
          break;
        }

        case potatoParser::BACKSLASH: {
          setState(146);
          match(potatoParser::BACKSLASH);
          break;
        }

        case potatoParser::T__4: {
          setState(147);
          match(potatoParser::T__4);
          break;
        }

        case potatoParser::T__5: {
          setState(148);
          match(potatoParser::T__5);
          break;
        }

        case potatoParser::SPACE: {
          setState(149);
          match(potatoParser::SPACE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Oneline_textContext ------------------------------------------------------------------

potatoParser::Oneline_textContext::Oneline_textContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<potatoParser::Text_signContext *> potatoParser::Oneline_textContext::text_sign() {
  return getRuleContexts<potatoParser::Text_signContext>();
}

potatoParser::Text_signContext* potatoParser::Oneline_textContext::text_sign(size_t i) {
  return getRuleContext<potatoParser::Text_signContext>(i);
}

std::vector<tree::TerminalNode *> potatoParser::Oneline_textContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::Oneline_textContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}

std::vector<tree::TerminalNode *> potatoParser::Oneline_textContext::BACKSLASH() {
  return getTokens(potatoParser::BACKSLASH);
}

tree::TerminalNode* potatoParser::Oneline_textContext::BACKSLASH(size_t i) {
  return getToken(potatoParser::BACKSLASH, i);
}


size_t potatoParser::Oneline_textContext::getRuleIndex() const {
  return potatoParser::RuleOneline_text;
}

void potatoParser::Oneline_textContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOneline_text(this);
}

void potatoParser::Oneline_textContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOneline_text(this);
}

potatoParser::Oneline_textContext* potatoParser::oneline_text() {
  Oneline_textContext *_localctx = _tracker.createInstance<Oneline_textContext>(_ctx, getState());
  enterRule(_localctx, 22, potatoParser::RuleOneline_text);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(159); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(159);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case potatoParser::T__0:
                case potatoParser::T__1:
                case potatoParser::T__2:
                case potatoParser::T__3:
                case potatoParser::TEXT: {
                  setState(155);
                  text_sign();
                  break;
                }

                case potatoParser::T__4: {
                  setState(156);
                  match(potatoParser::T__4);
                  break;
                }

                case potatoParser::T__5: {
                  setState(157);
                  match(potatoParser::T__5);
                  break;
                }

                case potatoParser::SPACE: {
                  setState(158);
                  match(potatoParser::SPACE);
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(161); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(170);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << potatoParser::T__0)
      | (1ULL << potatoParser::T__1)
      | (1ULL << potatoParser::T__2)
      | (1ULL << potatoParser::T__3)
      | (1ULL << potatoParser::T__4)
      | (1ULL << potatoParser::T__5)
      | (1ULL << potatoParser::BACKSLASH)
      | (1ULL << potatoParser::SPACE)
      | (1ULL << potatoParser::TEXT))) != 0)) {
      setState(168);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case potatoParser::T__0:
        case potatoParser::T__1:
        case potatoParser::T__2:
        case potatoParser::T__3:
        case potatoParser::TEXT: {
          setState(163);
          text_sign();
          break;
        }

        case potatoParser::BACKSLASH: {
          setState(164);
          match(potatoParser::BACKSLASH);
          break;
        }

        case potatoParser::T__4: {
          setState(165);
          match(potatoParser::T__4);
          break;
        }

        case potatoParser::T__5: {
          setState(166);
          match(potatoParser::T__5);
          break;
        }

        case potatoParser::SPACE: {
          setState(167);
          match(potatoParser::SPACE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(172);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Text_in_bracketContext ------------------------------------------------------------------

potatoParser::Text_in_bracketContext::Text_in_bracketContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<potatoParser::Text_signContext *> potatoParser::Text_in_bracketContext::text_sign() {
  return getRuleContexts<potatoParser::Text_signContext>();
}

potatoParser::Text_signContext* potatoParser::Text_in_bracketContext::text_sign(size_t i) {
  return getRuleContext<potatoParser::Text_signContext>(i);
}

std::vector<tree::TerminalNode *> potatoParser::Text_in_bracketContext::BACKSLASH() {
  return getTokens(potatoParser::BACKSLASH);
}

tree::TerminalNode* potatoParser::Text_in_bracketContext::BACKSLASH(size_t i) {
  return getToken(potatoParser::BACKSLASH, i);
}

std::vector<tree::TerminalNode *> potatoParser::Text_in_bracketContext::NEWLINE() {
  return getTokens(potatoParser::NEWLINE);
}

tree::TerminalNode* potatoParser::Text_in_bracketContext::NEWLINE(size_t i) {
  return getToken(potatoParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> potatoParser::Text_in_bracketContext::SPACE() {
  return getTokens(potatoParser::SPACE);
}

tree::TerminalNode* potatoParser::Text_in_bracketContext::SPACE(size_t i) {
  return getToken(potatoParser::SPACE, i);
}


size_t potatoParser::Text_in_bracketContext::getRuleIndex() const {
  return potatoParser::RuleText_in_bracket;
}

void potatoParser::Text_in_bracketContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_in_bracket(this);
}

void potatoParser::Text_in_bracketContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_in_bracket(this);
}

potatoParser::Text_in_bracketContext* potatoParser::text_in_bracket() {
  Text_in_bracketContext *_localctx = _tracker.createInstance<Text_in_bracketContext>(_ctx, getState());
  enterRule(_localctx, 24, potatoParser::RuleText_in_bracket);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(179); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(179);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case potatoParser::T__0:
                case potatoParser::T__1:
                case potatoParser::T__2:
                case potatoParser::T__3:
                case potatoParser::TEXT: {
                  setState(173);
                  text_sign();
                  break;
                }

                case potatoParser::BACKSLASH: {
                  setState(174);
                  match(potatoParser::BACKSLASH);
                  break;
                }

                case potatoParser::NEWLINE: {
                  setState(175);
                  match(potatoParser::NEWLINE);
                  break;
                }

                case potatoParser::T__4: {
                  setState(176);
                  match(potatoParser::T__4);
                  break;
                }

                case potatoParser::T__5: {
                  setState(177);
                  match(potatoParser::T__5);
                  break;
                }

                case potatoParser::SPACE: {
                  setState(178);
                  match(potatoParser::SPACE);
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(181); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Text_signContext ------------------------------------------------------------------

potatoParser::Text_signContext::Text_signContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> potatoParser::Text_signContext::TEXT() {
  return getTokens(potatoParser::TEXT);
}

tree::TerminalNode* potatoParser::Text_signContext::TEXT(size_t i) {
  return getToken(potatoParser::TEXT, i);
}


size_t potatoParser::Text_signContext::getRuleIndex() const {
  return potatoParser::RuleText_sign;
}

void potatoParser::Text_signContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_sign(this);
}

void potatoParser::Text_signContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_sign(this);
}

potatoParser::Text_signContext* potatoParser::text_sign() {
  Text_signContext *_localctx = _tracker.createInstance<Text_signContext>(_ctx, getState());
  enterRule(_localctx, 26, potatoParser::RuleText_sign);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(184); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(183);
              _la = _input->LA(1);
              if (!((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << potatoParser::T__0)
                | (1ULL << potatoParser::T__1)
                | (1ULL << potatoParser::T__2)
                | (1ULL << potatoParser::T__3)
                | (1ULL << potatoParser::TEXT))) != 0))) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(186); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> potatoParser::_decisionToDFA;
atn::PredictionContextCache potatoParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN potatoParser::_atn;
std::vector<uint16_t> potatoParser::_serializedATN;

std::vector<std::string> potatoParser::_ruleNames = {
  "potato", "box", "command", "property_entry", "proberty", "value", "paragraph", 
  "paragraph_without_bracket", "paragraph_bracket", "text", "oneline_text_first", 
  "oneline_text", "text_in_bracket", "text_sign"
};

std::vector<std::string> potatoParser::_literalNames = {
  "", "'['", "';'", "']'", "':'", "'{'", "'}'"
};

std::vector<std::string> potatoParser::_symbolicNames = {
  "", "", "", "", "", "", "", "BACKSLASH", "BACKSLASH_CURLED_BRACKET_OPEN", 
  "BACKSLASH_CURLED_BRACKET_CLOSE", "NEWLINE", "SPACE", "TEXT"
};

dfa::Vocabulary potatoParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> potatoParser::_tokenNames;

potatoParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0xe, 0xbf, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x3, 0x2, 0x5, 0x2, 0x20, 0xa, 
       0x2, 0x3, 0x2, 0x7, 0x2, 0x23, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x26, 
       0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x31, 0xa, 0x4, 0x3, 
       0x4, 0x7, 0x4, 0x34, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x37, 0xb, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x3b, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 
       0x3e, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x42, 0xa, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x5, 0x5, 0x46, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x6, 0x6, 0x6, 0x4b, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x4c, 0x3, 0x7, 
       0x6, 0x7, 0x50, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x51, 0x3, 0x8, 0x3, 
       0x8, 0x5, 0x8, 0x56, 0xa, 0x8, 0x3, 0x9, 0x5, 0x9, 0x59, 0xa, 0x9, 
       0x3, 0x9, 0x5, 0x9, 0x5c, 0xa, 0x9, 0x3, 0x9, 0x5, 0x9, 0x5f, 0xa, 
       0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x63, 0xa, 0x9, 0x3, 0x9, 0x5, 
       0x9, 0x66, 0xa, 0x9, 0x3, 0xa, 0x5, 0xa, 0x69, 0xa, 0xa, 0x3, 0xa, 
       0x5, 0xa, 0x6c, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x70, 0xa, 
       0xa, 0x3, 0xa, 0x5, 0xa, 0x73, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 
       0xa, 0x77, 0xa, 0xa, 0x3, 0xa, 0x5, 0xa, 0x7a, 0xa, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x7f, 0xa, 0xa, 0x3, 0xa, 0x5, 0xa, 
       0x82, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x87, 0xa, 
       0xb, 0xc, 0xb, 0xe, 0xb, 0x8a, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
       0xc, 0x3, 0xc, 0x6, 0xc, 0x90, 0xa, 0xc, 0xd, 0xc, 0xe, 0xc, 0x91, 
       0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x99, 
       0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x9c, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x3, 0xd, 0x6, 0xd, 0xa2, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 
       0xa3, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 
       0xab, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xae, 0xb, 0xd, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x6, 0xe, 0xb6, 0xa, 
       0xe, 0xd, 0xe, 0xe, 0xe, 0xb7, 0x3, 0xf, 0x6, 0xf, 0xbb, 0xa, 0xf, 
       0xd, 0xf, 0xe, 0xf, 0xbc, 0x3, 0xf, 0x2, 0x2, 0x10, 0x2, 0x4, 0x6, 
       0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x2, 
       0x4, 0x3, 0x2, 0xd, 0xe, 0x4, 0x2, 0x3, 0x6, 0xe, 0xe, 0x2, 0xe2, 
       0x2, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x4, 0x27, 0x3, 0x2, 0x2, 0x2, 0x6, 
       0x2a, 0x3, 0x2, 0x2, 0x2, 0x8, 0x3f, 0x3, 0x2, 0x2, 0x2, 0xa, 0x4a, 
       0x3, 0x2, 0x2, 0x2, 0xc, 0x4f, 0x3, 0x2, 0x2, 0x2, 0xe, 0x55, 0x3, 
       0x2, 0x2, 0x2, 0x10, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x68, 0x3, 0x2, 
       0x2, 0x2, 0x14, 0x83, 0x3, 0x2, 0x2, 0x2, 0x16, 0x8f, 0x3, 0x2, 0x2, 
       0x2, 0x18, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xb5, 0x3, 0x2, 0x2, 0x2, 
       0x1c, 0xba, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x20, 0x7, 0xc, 0x2, 0x2, 0x1f, 
       0x1e, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x24, 
       0x3, 0x2, 0x2, 0x2, 0x21, 0x23, 0x5, 0x4, 0x3, 0x2, 0x22, 0x21, 0x3, 
       0x2, 0x2, 0x2, 0x23, 0x26, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 
       0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x5, 0x6, 0x4, 0x2, 
       0x28, 0x29, 0x5, 0xe, 0x8, 0x2, 0x29, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2a, 
       0x2b, 0x7, 0x9, 0x2, 0x2, 0x2b, 0x3a, 0x7, 0xe, 0x2, 0x2, 0x2c, 0x2d, 
       0x7, 0x3, 0x2, 0x2, 0x2d, 0x35, 0x5, 0x8, 0x5, 0x2, 0x2e, 0x30, 0x7, 
       0x4, 0x2, 0x2, 0x2f, 0x31, 0x7, 0xd, 0x2, 0x2, 0x30, 0x2f, 0x3, 0x2, 
       0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 0x2, 0x2, 
       0x2, 0x32, 0x34, 0x5, 0x8, 0x5, 0x2, 0x33, 0x2e, 0x3, 0x2, 0x2, 0x2, 
       0x34, 0x37, 0x3, 0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 
       0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x38, 0x3, 0x2, 0x2, 0x2, 0x37, 0x35, 
       0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x7, 0x5, 0x2, 0x2, 0x39, 0x3b, 0x3, 
       0x2, 0x2, 0x2, 0x3a, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x3, 0x2, 
       0x2, 0x2, 0x3b, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3e, 0x7, 0xd, 0x2, 
       0x2, 0x3d, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 
       0x3e, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x41, 0x5, 0xa, 0x6, 0x2, 0x40, 
       0x42, 0x7, 0xd, 0x2, 0x2, 0x41, 0x40, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 
       0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x3, 0x2, 0x2, 0x2, 0x43, 0x45, 0x7, 
       0x6, 0x2, 0x2, 0x44, 0x46, 0x7, 0xd, 0x2, 0x2, 0x45, 0x44, 0x3, 0x2, 
       0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 
       0x2, 0x47, 0x48, 0x5, 0xc, 0x7, 0x2, 0x48, 0x9, 0x3, 0x2, 0x2, 0x2, 
       0x49, 0x4b, 0x9, 0x2, 0x2, 0x2, 0x4a, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 
       0x4c, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 
       0x3, 0x2, 0x2, 0x2, 0x4d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x50, 0x9, 
       0x2, 0x2, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 
       0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 0x2, 
       0x2, 0x52, 0xd, 0x3, 0x2, 0x2, 0x2, 0x53, 0x56, 0x5, 0x12, 0xa, 0x2, 
       0x54, 0x56, 0x5, 0x10, 0x9, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 
       0x55, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 0xf, 0x3, 0x2, 0x2, 0x2, 0x57, 
       0x59, 0x7, 0xd, 0x2, 0x2, 0x58, 0x57, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 
       0x3, 0x2, 0x2, 0x2, 0x59, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5c, 0x7, 
       0xc, 0x2, 0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x3, 0x2, 
       0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5f, 0x5, 0x14, 
       0xb, 0x2, 0x5e, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x3, 0x2, 0x2, 
       0x2, 0x5f, 0x65, 0x3, 0x2, 0x2, 0x2, 0x60, 0x66, 0x7, 0xc, 0x2, 0x2, 
       0x61, 0x63, 0x7, 0xc, 0x2, 0x2, 0x62, 0x61, 0x3, 0x2, 0x2, 0x2, 0x62, 
       0x63, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x66, 
       0x7, 0x2, 0x2, 0x3, 0x65, 0x60, 0x3, 0x2, 0x2, 0x2, 0x65, 0x62, 0x3, 
       0x2, 0x2, 0x2, 0x66, 0x11, 0x3, 0x2, 0x2, 0x2, 0x67, 0x69, 0x7, 0xd, 
       0x2, 0x2, 0x68, 0x67, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x3, 0x2, 0x2, 
       0x2, 0x69, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6c, 0x7, 0xc, 0x2, 0x2, 
       0x6b, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6c, 
       0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6f, 0x7, 0xa, 0x2, 0x2, 0x6e, 0x70, 
       0x7, 0xd, 0x2, 0x2, 0x6f, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 
       0x2, 0x2, 0x2, 0x70, 0x72, 0x3, 0x2, 0x2, 0x2, 0x71, 0x73, 0x7, 0xc, 
       0x2, 0x2, 0x72, 0x71, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 
       0x2, 0x73, 0x74, 0x3, 0x2, 0x2, 0x2, 0x74, 0x76, 0x5, 0x1a, 0xe, 
       0x2, 0x75, 0x77, 0x7, 0xd, 0x2, 0x2, 0x76, 0x75, 0x3, 0x2, 0x2, 0x2, 
       0x76, 0x77, 0x3, 0x2, 0x2, 0x2, 0x77, 0x79, 0x3, 0x2, 0x2, 0x2, 0x78, 
       0x7a, 0x7, 0xc, 0x2, 0x2, 0x79, 0x78, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 
       0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x81, 0x7, 
       0xb, 0x2, 0x2, 0x7c, 0x82, 0x7, 0xc, 0x2, 0x2, 0x7d, 0x7f, 0x7, 0xc, 
       0x2, 0x2, 0x7e, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x3, 0x2, 0x2, 
       0x2, 0x7f, 0x80, 0x3, 0x2, 0x2, 0x2, 0x80, 0x82, 0x7, 0x2, 0x2, 0x3, 
       0x81, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x82, 
       0x13, 0x3, 0x2, 0x2, 0x2, 0x83, 0x88, 0x5, 0x16, 0xc, 0x2, 0x84, 
       0x85, 0x7, 0xc, 0x2, 0x2, 0x85, 0x87, 0x5, 0x18, 0xd, 0x2, 0x86, 
       0x84, 0x3, 0x2, 0x2, 0x2, 0x87, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 
       0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x3, 0x2, 0x2, 0x2, 0x89, 0x15, 0x3, 
       0x2, 0x2, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x90, 0x5, 0x1c, 
       0xf, 0x2, 0x8c, 0x90, 0x7, 0x7, 0x2, 0x2, 0x8d, 0x90, 0x7, 0x8, 0x2, 
       0x2, 0x8e, 0x90, 0x7, 0xd, 0x2, 0x2, 0x8f, 0x8b, 0x3, 0x2, 0x2, 0x2, 
       0x8f, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8f, 
       0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x3, 0x2, 0x2, 0x2, 0x91, 0x8f, 
       0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 0x9a, 0x3, 
       0x2, 0x2, 0x2, 0x93, 0x99, 0x5, 0x1c, 0xf, 0x2, 0x94, 0x99, 0x7, 
       0x9, 0x2, 0x2, 0x95, 0x99, 0x7, 0x7, 0x2, 0x2, 0x96, 0x99, 0x7, 0x8, 
       0x2, 0x2, 0x97, 0x99, 0x7, 0xd, 0x2, 0x2, 0x98, 0x93, 0x3, 0x2, 0x2, 
       0x2, 0x98, 0x94, 0x3, 0x2, 0x2, 0x2, 0x98, 0x95, 0x3, 0x2, 0x2, 0x2, 
       0x98, 0x96, 0x3, 0x2, 0x2, 0x2, 0x98, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 
       0x9c, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 
       0x3, 0x2, 0x2, 0x2, 0x9b, 0x17, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 
       0x2, 0x2, 0x2, 0x9d, 0xa2, 0x5, 0x1c, 0xf, 0x2, 0x9e, 0xa2, 0x7, 
       0x7, 0x2, 0x2, 0x9f, 0xa2, 0x7, 0x8, 0x2, 0x2, 0xa0, 0xa2, 0x7, 0xd, 
       0x2, 0x2, 0xa1, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x9e, 0x3, 0x2, 0x2, 
       0x2, 0xa1, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa0, 0x3, 0x2, 0x2, 0x2, 
       0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa3, 
       0xa4, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xac, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xab, 
       0x5, 0x1c, 0xf, 0x2, 0xa6, 0xab, 0x7, 0x9, 0x2, 0x2, 0xa7, 0xab, 
       0x7, 0x7, 0x2, 0x2, 0xa8, 0xab, 0x7, 0x8, 0x2, 0x2, 0xa9, 0xab, 0x7, 
       0xd, 0x2, 0x2, 0xaa, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa6, 0x3, 0x2, 
       0x2, 0x2, 0xaa, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa8, 0x3, 0x2, 0x2, 
       0x2, 0xaa, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xab, 0xae, 0x3, 0x2, 0x2, 0x2, 
       0xac, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x3, 0x2, 0x2, 0x2, 0xad, 
       0x19, 0x3, 0x2, 0x2, 0x2, 0xae, 0xac, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb6, 
       0x5, 0x1c, 0xf, 0x2, 0xb0, 0xb6, 0x7, 0x9, 0x2, 0x2, 0xb1, 0xb6, 
       0x7, 0xc, 0x2, 0x2, 0xb2, 0xb6, 0x7, 0x7, 0x2, 0x2, 0xb3, 0xb6, 0x7, 
       0x8, 0x2, 0x2, 0xb4, 0xb6, 0x7, 0xd, 0x2, 0x2, 0xb5, 0xaf, 0x3, 0x2, 
       0x2, 0x2, 0xb5, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb1, 0x3, 0x2, 0x2, 
       0x2, 0xb5, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 
       0xb5, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xb7, 
       0xb5, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb8, 0x1b, 
       0x3, 0x2, 0x2, 0x2, 0xb9, 0xbb, 0x9, 0x3, 0x2, 0x2, 0xba, 0xb9, 0x3, 
       0x2, 0x2, 0x2, 0xbb, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xba, 0x3, 0x2, 
       0x2, 0x2, 0xbc, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbd, 0x1d, 0x3, 0x2, 0x2, 
       0x2, 0x26, 0x1f, 0x24, 0x30, 0x35, 0x3a, 0x3d, 0x41, 0x45, 0x4c, 
       0x51, 0x55, 0x58, 0x5b, 0x5e, 0x62, 0x65, 0x68, 0x6b, 0x6f, 0x72, 
       0x76, 0x79, 0x7e, 0x81, 0x88, 0x8f, 0x91, 0x98, 0x9a, 0xa1, 0xa3, 
       0xaa, 0xac, 0xb5, 0xb7, 0xbc, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

potatoParser::Initializer potatoParser::_init;
