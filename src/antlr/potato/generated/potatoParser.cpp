
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
    setState(21);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == potatoParser::BACKSLASH) {
      setState(18);
      box();
      setState(23);
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
    setState(24);
    command();
    setState(25);
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
    setState(27);
    match(potatoParser::BACKSLASH);
    setState(28);
    match(potatoParser::TEXT);
    setState(43);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(29);
      match(potatoParser::T__0);
      setState(30);
      property_entry();
      setState(38);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == potatoParser::T__1) {
        setState(31);
        match(potatoParser::T__1);
        setState(33);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == potatoParser::T__2) {
          setState(32);
          match(potatoParser::T__2);
        }
        setState(35);
        property_entry();
        setState(40);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(41);
      match(potatoParser::T__3);
      break;
    }

    default:
      break;
    }
    setState(46);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(45);
      match(potatoParser::T__2);
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

potatoParser::Text_colonContext* potatoParser::Property_entryContext::text_colon() {
  return getRuleContext<potatoParser::Text_colonContext>(0);
}

potatoParser::ValueContext* potatoParser::Property_entryContext::value() {
  return getRuleContext<potatoParser::ValueContext>(0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    text_colon();
    setState(49);
    value();
   
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
  enterRule(_localctx, 8, potatoParser::RuleValue);
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
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == potatoParser::T__2

    || _la == potatoParser::TEXT) {
      setState(51);
      _la = _input->LA(1);
      if (!(_la == potatoParser::T__2

      || _la == potatoParser::TEXT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(56);
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

//----------------- ParagraphContext ------------------------------------------------------------------

potatoParser::ParagraphContext::ParagraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> potatoParser::ParagraphContext::NEWLINE() {
  return getTokens(potatoParser::NEWLINE);
}

tree::TerminalNode* potatoParser::ParagraphContext::NEWLINE(size_t i) {
  return getToken(potatoParser::NEWLINE, i);
}

tree::TerminalNode* potatoParser::ParagraphContext::EOF() {
  return getToken(potatoParser::EOF, 0);
}

potatoParser::TextContext* potatoParser::ParagraphContext::text() {
  return getRuleContext<potatoParser::TextContext>(0);
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
  enterRule(_localctx, 10, potatoParser::RuleParagraph);
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
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(58);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == potatoParser::NEWLINE) {
        setState(57);
        match(potatoParser::NEWLINE);
      }
      setState(60);
      text();
      break;
    }

    default:
      break;
    }
    setState(68);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(63);
      match(potatoParser::NEWLINE);
      break;
    }

    case 2: {
      setState(65);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == potatoParser::NEWLINE) {
        setState(64);
        match(potatoParser::NEWLINE);
      }
      setState(67);
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

std::vector<potatoParser::Oneline_textContext *> potatoParser::TextContext::oneline_text() {
  return getRuleContexts<potatoParser::Oneline_textContext>();
}

potatoParser::Oneline_textContext* potatoParser::TextContext::oneline_text(size_t i) {
  return getRuleContext<potatoParser::Oneline_textContext>(i);
}

std::vector<tree::TerminalNode *> potatoParser::TextContext::NEWLINE() {
  return getTokens(potatoParser::NEWLINE);
}

tree::TerminalNode* potatoParser::TextContext::NEWLINE(size_t i) {
  return getToken(potatoParser::NEWLINE, i);
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
  enterRule(_localctx, 12, potatoParser::RuleText);

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
    setState(70);
    oneline_text();
    setState(75);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(71);
        match(potatoParser::NEWLINE);
        setState(72);
        oneline_text(); 
      }
      setState(77);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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

std::vector<tree::TerminalNode *> potatoParser::Oneline_textContext::TEXT() {
  return getTokens(potatoParser::TEXT);
}

tree::TerminalNode* potatoParser::Oneline_textContext::TEXT(size_t i) {
  return getToken(potatoParser::TEXT, i);
}

std::vector<potatoParser::Text_colonContext *> potatoParser::Oneline_textContext::text_colon() {
  return getRuleContexts<potatoParser::Text_colonContext>();
}

potatoParser::Text_colonContext* potatoParser::Oneline_textContext::text_colon(size_t i) {
  return getRuleContext<potatoParser::Text_colonContext>(i);
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
  enterRule(_localctx, 14, potatoParser::RuleOneline_text);
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
    setState(84); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(84);
              _errHandler->sync(this);
              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
              case 1: {
                setState(78);
                match(potatoParser::TEXT);
                break;
              }

              case 2: {
                setState(79);
                match(potatoParser::T__2);
                break;
              }

              case 3: {
                setState(80);
                text_colon();
                break;
              }

              case 4: {
                setState(81);
                match(potatoParser::T__1);
                break;
              }

              case 5: {
                setState(82);
                match(potatoParser::T__0);
                break;
              }

              case 6: {
                setState(83);
                match(potatoParser::T__3);
                break;
              }

              default:
                break;
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(86); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << potatoParser::T__0)
      | (1ULL << potatoParser::T__1)
      | (1ULL << potatoParser::T__2)
      | (1ULL << potatoParser::T__3)
      | (1ULL << potatoParser::BACKSLASH)
      | (1ULL << potatoParser::TEXT))) != 0)) {
      setState(95);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(88);
        match(potatoParser::TEXT);
        break;
      }

      case 2: {
        setState(89);
        match(potatoParser::T__2);
        break;
      }

      case 3: {
        setState(90);
        text_colon();
        break;
      }

      case 4: {
        setState(91);
        match(potatoParser::T__1);
        break;
      }

      case 5: {
        setState(92);
        match(potatoParser::T__0);
        break;
      }

      case 6: {
        setState(93);
        match(potatoParser::T__3);
        break;
      }

      case 7: {
        setState(94);
        match(potatoParser::BACKSLASH);
        break;
      }

      default:
        break;
      }
      setState(99);
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

//----------------- Text_colonContext ------------------------------------------------------------------

potatoParser::Text_colonContext::Text_colonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::Text_colonContext::TEXT() {
  return getToken(potatoParser::TEXT, 0);
}


size_t potatoParser::Text_colonContext::getRuleIndex() const {
  return potatoParser::RuleText_colon;
}

void potatoParser::Text_colonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_colon(this);
}

void potatoParser::Text_colonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_colon(this);
}

potatoParser::Text_colonContext* potatoParser::text_colon() {
  Text_colonContext *_localctx = _tracker.createInstance<Text_colonContext>(_ctx, getState());
  enterRule(_localctx, 16, potatoParser::RuleText_colon);
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
    setState(100);
    match(potatoParser::TEXT);
    setState(102);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::T__2) {
      setState(101);
      match(potatoParser::T__2);
    }
    setState(104);
    match(potatoParser::T__4);
    setState(106);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(105);
      match(potatoParser::T__2);
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

// Static vars and initialization.
std::vector<dfa::DFA> potatoParser::_decisionToDFA;
atn::PredictionContextCache potatoParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN potatoParser::_atn;
std::vector<uint16_t> potatoParser::_serializedATN;

std::vector<std::string> potatoParser::_ruleNames = {
  "potato", "box", "command", "property_entry", "value", "paragraph", "text", 
  "oneline_text", "text_colon"
};

std::vector<std::string> potatoParser::_literalNames = {
  "", "'['", "';'", "' '", "']'", "':'"
};

std::vector<std::string> potatoParser::_symbolicNames = {
  "", "", "", "", "", "", "BACKSLASH", "NEWLINE", "TEXT"
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
       0x3, 0xa, 0x6f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x3, 0x2, 0x7, 0x2, 0x16, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x19, 0xb, 
       0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x24, 0xa, 0x4, 0x3, 0x4, 
       0x7, 0x4, 0x27, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2a, 0xb, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x5, 0x4, 0x2e, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0x31, 
       0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x7, 0x6, 0x37, 
       0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x3a, 0xb, 0x6, 0x3, 0x7, 0x5, 0x7, 
       0x3d, 0xa, 0x7, 0x3, 0x7, 0x5, 0x7, 0x40, 0xa, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x5, 0x7, 0x44, 0xa, 0x7, 0x3, 0x7, 0x5, 0x7, 0x47, 0xa, 0x7, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x4c, 0xa, 0x8, 0xc, 0x8, 
       0xe, 0x8, 0x4f, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x3, 0x9, 0x6, 0x9, 0x57, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 
       0x58, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x7, 0x9, 0x62, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x65, 0xb, 
       0x9, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x69, 0xa, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x5, 0xa, 0x6d, 0xa, 0xa, 0x3, 0xa, 0x2, 0x2, 0xb, 0x2, 0x4, 
       0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x2, 0x3, 0x4, 0x2, 0x5, 0x5, 
       0xa, 0xa, 0x2, 0x7f, 0x2, 0x17, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1a, 0x3, 
       0x2, 0x2, 0x2, 0x6, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x8, 0x32, 0x3, 0x2, 
       0x2, 0x2, 0xa, 0x38, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3f, 0x3, 0x2, 0x2, 
       0x2, 0xe, 0x48, 0x3, 0x2, 0x2, 0x2, 0x10, 0x56, 0x3, 0x2, 0x2, 0x2, 
       0x12, 0x66, 0x3, 0x2, 0x2, 0x2, 0x14, 0x16, 0x5, 0x4, 0x3, 0x2, 0x15, 
       0x14, 0x3, 0x2, 0x2, 0x2, 0x16, 0x19, 0x3, 0x2, 0x2, 0x2, 0x17, 0x15, 
       0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 0x3, 0x2, 0x2, 0x2, 0x18, 0x3, 0x3, 
       0x2, 0x2, 0x2, 0x19, 0x17, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x5, 0x6, 
       0x4, 0x2, 0x1b, 0x1c, 0x5, 0xc, 0x7, 0x2, 0x1c, 0x5, 0x3, 0x2, 0x2, 
       0x2, 0x1d, 0x1e, 0x7, 0x8, 0x2, 0x2, 0x1e, 0x2d, 0x7, 0xa, 0x2, 0x2, 
       0x1f, 0x20, 0x7, 0x3, 0x2, 0x2, 0x20, 0x28, 0x5, 0x8, 0x5, 0x2, 0x21, 
       0x23, 0x7, 0x4, 0x2, 0x2, 0x22, 0x24, 0x7, 0x5, 0x2, 0x2, 0x23, 0x22, 
       0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 
       0x2, 0x2, 0x2, 0x25, 0x27, 0x5, 0x8, 0x5, 0x2, 0x26, 0x21, 0x3, 0x2, 
       0x2, 0x2, 0x27, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x28, 0x26, 0x3, 0x2, 0x2, 
       0x2, 0x28, 0x29, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2b, 0x3, 0x2, 0x2, 0x2, 
       0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x7, 0x6, 0x2, 0x2, 0x2c, 
       0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 
       0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x31, 0x7, 
       0x5, 0x2, 0x2, 0x30, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 
       0x2, 0x2, 0x31, 0x7, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x5, 0x12, 0xa, 
       0x2, 0x33, 0x34, 0x5, 0xa, 0x6, 0x2, 0x34, 0x9, 0x3, 0x2, 0x2, 0x2, 
       0x35, 0x37, 0x9, 0x2, 0x2, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 
       0x3a, 0x3, 0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 
       0x3, 0x2, 0x2, 0x2, 0x39, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x38, 0x3, 
       0x2, 0x2, 0x2, 0x3b, 0x3d, 0x7, 0x9, 0x2, 0x2, 0x3c, 0x3b, 0x3, 0x2, 
       0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 
       0x2, 0x3e, 0x40, 0x5, 0xe, 0x8, 0x2, 0x3f, 0x3c, 0x3, 0x2, 0x2, 0x2, 
       0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x46, 0x3, 0x2, 0x2, 0x2, 0x41, 
       0x47, 0x7, 0x9, 0x2, 0x2, 0x42, 0x44, 0x7, 0x9, 0x2, 0x2, 0x43, 0x42, 
       0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x3, 
       0x2, 0x2, 0x2, 0x45, 0x47, 0x7, 0x2, 0x2, 0x3, 0x46, 0x41, 0x3, 0x2, 
       0x2, 0x2, 0x46, 0x43, 0x3, 0x2, 0x2, 0x2, 0x47, 0xd, 0x3, 0x2, 0x2, 
       0x2, 0x48, 0x4d, 0x5, 0x10, 0x9, 0x2, 0x49, 0x4a, 0x7, 0x9, 0x2, 
       0x2, 0x4a, 0x4c, 0x5, 0x10, 0x9, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 
       0x2, 0x4c, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4b, 0x3, 0x2, 0x2, 0x2, 
       0x4d, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4e, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4f, 
       0x4d, 0x3, 0x2, 0x2, 0x2, 0x50, 0x57, 0x7, 0xa, 0x2, 0x2, 0x51, 0x57, 
       0x7, 0x5, 0x2, 0x2, 0x52, 0x57, 0x5, 0x12, 0xa, 0x2, 0x53, 0x57, 
       0x7, 0x4, 0x2, 0x2, 0x54, 0x57, 0x7, 0x3, 0x2, 0x2, 0x55, 0x57, 0x7, 
       0x6, 0x2, 0x2, 0x56, 0x50, 0x3, 0x2, 0x2, 0x2, 0x56, 0x51, 0x3, 0x2, 
       0x2, 0x2, 0x56, 0x52, 0x3, 0x2, 0x2, 0x2, 0x56, 0x53, 0x3, 0x2, 0x2, 
       0x2, 0x56, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 0x55, 0x3, 0x2, 0x2, 0x2, 
       0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 0x58, 0x56, 0x3, 0x2, 0x2, 0x2, 0x58, 
       0x59, 0x3, 0x2, 0x2, 0x2, 0x59, 0x63, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x62, 
       0x7, 0xa, 0x2, 0x2, 0x5b, 0x62, 0x7, 0x5, 0x2, 0x2, 0x5c, 0x62, 0x5, 
       0x12, 0xa, 0x2, 0x5d, 0x62, 0x7, 0x4, 0x2, 0x2, 0x5e, 0x62, 0x7, 
       0x3, 0x2, 0x2, 0x5f, 0x62, 0x7, 0x6, 0x2, 0x2, 0x60, 0x62, 0x7, 0x8, 
       0x2, 0x2, 0x61, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x61, 0x5b, 0x3, 0x2, 0x2, 
       0x2, 0x61, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x61, 0x5d, 0x3, 0x2, 0x2, 0x2, 
       0x61, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 
       0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 0x2, 0x63, 0x61, 
       0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x11, 0x3, 
       0x2, 0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x66, 0x68, 0x7, 0xa, 
       0x2, 0x2, 0x67, 0x69, 0x7, 0x5, 0x2, 0x2, 0x68, 0x67, 0x3, 0x2, 0x2, 
       0x2, 0x68, 0x69, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 
       0x6a, 0x6c, 0x7, 0x7, 0x2, 0x2, 0x6b, 0x6d, 0x7, 0x5, 0x2, 0x2, 0x6c, 
       0x6b, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x13, 
       0x3, 0x2, 0x2, 0x2, 0x13, 0x17, 0x23, 0x28, 0x2d, 0x30, 0x38, 0x3c, 
       0x3f, 0x43, 0x46, 0x4d, 0x56, 0x58, 0x61, 0x63, 0x68, 0x6c, 
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
