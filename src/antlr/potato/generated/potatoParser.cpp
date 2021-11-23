
// Generated from potato.g4 by ANTLR 4.9.3


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
    setState(31); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(30);
      box();
      setState(33); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == potatoParser::T__6);
   
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

tree::TerminalNode* potatoParser::BoxContext::EOF() {
  return getToken(potatoParser::EOF, 0);
}

std::vector<potatoParser::WsContext *> potatoParser::BoxContext::ws() {
  return getRuleContexts<potatoParser::WsContext>();
}

potatoParser::WsContext* potatoParser::BoxContext::ws(size_t i) {
  return getRuleContext<potatoParser::WsContext>(i);
}

potatoParser::Property_listContext* potatoParser::BoxContext::property_list() {
  return getRuleContext<potatoParser::Property_listContext>(0);
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
    setState(35);
    command();
    setState(39);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(36);
        ws(); 
      }
      setState(41);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
    setState(43);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == potatoParser::T__5) {
      setState(42);
      property_list();
    }
    setState(45);
    paragraph();
    setState(58);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case potatoParser::T__0:
      case potatoParser::T__1: {
        setState(49);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == potatoParser::T__0) {
          setState(46);
          match(potatoParser::T__0);
          setState(51);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(53); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(52);
          match(potatoParser::T__1);
          setState(55); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == potatoParser::T__1);
        break;
      }

      case potatoParser::EOF: {
        setState(57);
        match(potatoParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
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

potatoParser::Text_in_bracketContext* potatoParser::ParagraphContext::text_in_bracket() {
  return getRuleContext<potatoParser::Text_in_bracketContext>(0);
}

std::vector<potatoParser::WsContext *> potatoParser::ParagraphContext::ws() {
  return getRuleContexts<potatoParser::WsContext>();
}

potatoParser::WsContext* potatoParser::ParagraphContext::ws(size_t i) {
  return getRuleContext<potatoParser::WsContext>(i);
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
  enterRule(_localctx, 4, potatoParser::RuleParagraph);
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
    setState(75);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(63);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == potatoParser::T__0

      || _la == potatoParser::T__1) {
        setState(60);
        ws();
        setState(65);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(66);
      text_in_bracket();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(70);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(67);
          ws(); 
        }
        setState(72);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
      }
      setState(73);
      text();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);

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

potatoParser::Oneline_textContext* potatoParser::TextContext::oneline_text() {
  return getRuleContext<potatoParser::Oneline_textContext>(0);
}

potatoParser::Multiline_textContext* potatoParser::TextContext::multiline_text() {
  return getRuleContext<potatoParser::Multiline_textContext>(0);
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
  enterRule(_localctx, 6, potatoParser::RuleText);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(79);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(77);
      oneline_text();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(78);
      multiline_text();
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

//----------------- Multiline_textContext ------------------------------------------------------------------

potatoParser::Multiline_textContext::Multiline_textContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<potatoParser::Oneline_textContext *> potatoParser::Multiline_textContext::oneline_text() {
  return getRuleContexts<potatoParser::Oneline_textContext>();
}

potatoParser::Oneline_textContext* potatoParser::Multiline_textContext::oneline_text(size_t i) {
  return getRuleContext<potatoParser::Oneline_textContext>(i);
}


size_t potatoParser::Multiline_textContext::getRuleIndex() const {
  return potatoParser::RuleMultiline_text;
}

void potatoParser::Multiline_textContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiline_text(this);
}

void potatoParser::Multiline_textContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiline_text(this);
}

potatoParser::Multiline_textContext* potatoParser::multiline_text() {
  Multiline_textContext *_localctx = _tracker.createInstance<Multiline_textContext>(_ctx, getState());
  enterRule(_localctx, 8, potatoParser::RuleMultiline_text);
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
    setState(93); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(81);
              oneline_text();
              setState(85);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while (_la == potatoParser::T__0) {
                setState(82);
                match(potatoParser::T__0);
                setState(87);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
              setState(89); 
              _errHandler->sync(this);
              _la = _input->LA(1);
              do {
                setState(88);
                match(potatoParser::T__1);
                setState(91); 
                _errHandler->sync(this);
                _la = _input->LA(1);
              } while (_la == potatoParser::T__1);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(95); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(97);
    oneline_text();
   
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

potatoParser::First_wordContext* potatoParser::Oneline_textContext::first_word() {
  return getRuleContext<potatoParser::First_wordContext>(0);
}

std::vector<potatoParser::Every_letter_wordContext *> potatoParser::Oneline_textContext::every_letter_word() {
  return getRuleContexts<potatoParser::Every_letter_wordContext>();
}

potatoParser::Every_letter_wordContext* potatoParser::Oneline_textContext::every_letter_word(size_t i) {
  return getRuleContext<potatoParser::Every_letter_wordContext>(i);
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
  enterRule(_localctx, 10, potatoParser::RuleOneline_text);

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
    setState(99);
    first_word();
    setState(103);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(100);
        every_letter_word(); 
      }
      setState(105);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- First_wordContext ------------------------------------------------------------------

potatoParser::First_wordContext::First_wordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::First_wordContext::WORD() {
  return getToken(potatoParser::WORD, 0);
}

tree::TerminalNode* potatoParser::First_wordContext::SPECIAL_CHARACTER() {
  return getToken(potatoParser::SPECIAL_CHARACTER, 0);
}


size_t potatoParser::First_wordContext::getRuleIndex() const {
  return potatoParser::RuleFirst_word;
}

void potatoParser::First_wordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFirst_word(this);
}

void potatoParser::First_wordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFirst_word(this);
}

potatoParser::First_wordContext* potatoParser::first_word() {
  First_wordContext *_localctx = _tracker.createInstance<First_wordContext>(_ctx, getState());
  enterRule(_localctx, 12, potatoParser::RuleFirst_word);
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
    setState(106);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << potatoParser::T__0)
      | (1ULL << potatoParser::T__2)
      | (1ULL << potatoParser::T__3)
      | (1ULL << potatoParser::T__4)
      | (1ULL << potatoParser::SPECIAL_CHARACTER)
      | (1ULL << potatoParser::WORD))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Every_letter_wordContext ------------------------------------------------------------------

potatoParser::Every_letter_wordContext::Every_letter_wordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

potatoParser::First_wordContext* potatoParser::Every_letter_wordContext::first_word() {
  return getRuleContext<potatoParser::First_wordContext>(0);
}


size_t potatoParser::Every_letter_wordContext::getRuleIndex() const {
  return potatoParser::RuleEvery_letter_word;
}

void potatoParser::Every_letter_wordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEvery_letter_word(this);
}

void potatoParser::Every_letter_wordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEvery_letter_word(this);
}

potatoParser::Every_letter_wordContext* potatoParser::every_letter_word() {
  Every_letter_wordContext *_localctx = _tracker.createInstance<Every_letter_wordContext>(_ctx, getState());
  enterRule(_localctx, 14, potatoParser::RuleEvery_letter_word);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(111);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case potatoParser::T__0:
      case potatoParser::T__2:
      case potatoParser::T__3:
      case potatoParser::T__4:
      case potatoParser::SPECIAL_CHARACTER:
      case potatoParser::WORD: {
        enterOuterAlt(_localctx, 1);
        setState(108);
        first_word();
        break;
      }

      case potatoParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(109);
        match(potatoParser::T__5);
        break;
      }

      case potatoParser::T__6: {
        enterOuterAlt(_localctx, 3);
        setState(110);
        match(potatoParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_listContext ------------------------------------------------------------------

potatoParser::Property_listContext::Property_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<potatoParser::Property_entryContext *> potatoParser::Property_listContext::property_entry() {
  return getRuleContexts<potatoParser::Property_entryContext>();
}

potatoParser::Property_entryContext* potatoParser::Property_listContext::property_entry(size_t i) {
  return getRuleContext<potatoParser::Property_entryContext>(i);
}

std::vector<potatoParser::WsContext *> potatoParser::Property_listContext::ws() {
  return getRuleContexts<potatoParser::WsContext>();
}

potatoParser::WsContext* potatoParser::Property_listContext::ws(size_t i) {
  return getRuleContext<potatoParser::WsContext>(i);
}


size_t potatoParser::Property_listContext::getRuleIndex() const {
  return potatoParser::RuleProperty_list;
}

void potatoParser::Property_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_list(this);
}

void potatoParser::Property_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_list(this);
}

potatoParser::Property_listContext* potatoParser::property_list() {
  Property_listContext *_localctx = _tracker.createInstance<Property_listContext>(_ctx, getState());
  enterRule(_localctx, 16, potatoParser::RuleProperty_list);
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
    setState(135);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(113);
      match(potatoParser::T__5);
      setState(114);
      property_entry();
      setState(119);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(115);
          match(potatoParser::T__3);
          setState(116);
          property_entry(); 
        }
        setState(121);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
      }
      setState(129);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == potatoParser::T__3) {
        setState(122);
        match(potatoParser::T__3);
        setState(126);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == potatoParser::T__0

        || _la == potatoParser::T__1) {
          setState(123);
          ws();
          setState(128);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(131);
      match(potatoParser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(133);
      match(potatoParser::T__5);
      setState(134);
      match(potatoParser::T__4);
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

potatoParser::PropertyContext* potatoParser::Property_entryContext::property() {
  return getRuleContext<potatoParser::PropertyContext>(0);
}

potatoParser::ValueContext* potatoParser::Property_entryContext::value() {
  return getRuleContext<potatoParser::ValueContext>(0);
}

std::vector<potatoParser::WsContext *> potatoParser::Property_entryContext::ws() {
  return getRuleContexts<potatoParser::WsContext>();
}

potatoParser::WsContext* potatoParser::Property_entryContext::ws(size_t i) {
  return getRuleContext<potatoParser::WsContext>(i);
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
  enterRule(_localctx, 18, potatoParser::RuleProperty_entry);

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
    setState(140);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(137);
        ws(); 
      }
      setState(142);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
    setState(143);
    property();
    setState(147);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(144);
        ws(); 
      }
      setState(149);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
    setState(150);
    match(potatoParser::T__2);
    setState(154);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(151);
        ws(); 
      }
      setState(156);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
    setState(157);
    value();
    setState(161);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(158);
        ws(); 
      }
      setState(163);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyContext ------------------------------------------------------------------

potatoParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::PropertyContext::WORD() {
  return getToken(potatoParser::WORD, 0);
}


size_t potatoParser::PropertyContext::getRuleIndex() const {
  return potatoParser::RuleProperty;
}

void potatoParser::PropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty(this);
}

void potatoParser::PropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty(this);
}

potatoParser::PropertyContext* potatoParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 20, potatoParser::RuleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(potatoParser::WORD);
   
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

std::vector<tree::TerminalNode *> potatoParser::ValueContext::WORD() {
  return getTokens(potatoParser::WORD);
}

tree::TerminalNode* potatoParser::ValueContext::WORD(size_t i) {
  return getToken(potatoParser::WORD, i);
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
  enterRule(_localctx, 22, potatoParser::RuleValue);
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
    setState(175);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(166);
      match(potatoParser::WORD);
      setState(170);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(167);
          _la = _input->LA(1);
          if (!(_la == potatoParser::T__0

          || _la == potatoParser::WORD)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          } 
        }
        setState(172);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      }
      setState(173);
      match(potatoParser::WORD);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(174);
      match(potatoParser::WORD);
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

//----------------- CommandContext ------------------------------------------------------------------

potatoParser::CommandContext::CommandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* potatoParser::CommandContext::WORD() {
  return getToken(potatoParser::WORD, 0);
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
  enterRule(_localctx, 24, potatoParser::RuleCommand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(potatoParser::T__6);
    setState(178);
    match(potatoParser::WORD);
   
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

tree::TerminalNode* potatoParser::Text_in_bracketContext::TEXT_BRACKET() {
  return getToken(potatoParser::TEXT_BRACKET, 0);
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
  enterRule(_localctx, 26, potatoParser::RuleText_in_bracket);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(potatoParser::TEXT_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WsContext ------------------------------------------------------------------

potatoParser::WsContext::WsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t potatoParser::WsContext::getRuleIndex() const {
  return potatoParser::RuleWs;
}

void potatoParser::WsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWs(this);
}

void potatoParser::WsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<potatoListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWs(this);
}

potatoParser::WsContext* potatoParser::ws() {
  WsContext *_localctx = _tracker.createInstance<WsContext>(_ctx, getState());
  enterRule(_localctx, 28, potatoParser::RuleWs);
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
    setState(182);
    _la = _input->LA(1);
    if (!(_la == potatoParser::T__0

    || _la == potatoParser::T__1)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
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
  "potato", "box", "paragraph", "text", "multiline_text", "oneline_text", 
  "first_word", "every_letter_word", "property_list", "property_entry", 
  "property", "value", "command", "text_in_bracket", "ws"
};

std::vector<std::string> potatoParser::_literalNames = {
  "", "' '", "'\n'", "':'", "';'", "']'", "'['", "'\\'"
};

std::vector<std::string> potatoParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "SPECIAL_CHARACTER", "WORD", "TEXT_BRACKET"
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
       0x3, 0xc, 0xbb, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 
       0x6, 0x2, 0x22, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x23, 0x3, 0x3, 0x3, 
       0x3, 0x7, 0x3, 0x28, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x2b, 0xb, 0x3, 
       0x3, 0x3, 0x5, 0x3, 0x2e, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 
       0x32, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x35, 0xb, 0x3, 0x3, 0x3, 0x6, 
       0x3, 0x38, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x39, 0x3, 0x3, 0x5, 0x3, 
       0x3d, 0xa, 0x3, 0x3, 0x4, 0x7, 0x4, 0x40, 0xa, 0x4, 0xc, 0x4, 0xe, 
       0x4, 0x43, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x47, 0xa, 0x4, 
       0xc, 0x4, 0xe, 0x4, 0x4a, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 
       0x4e, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x52, 0xa, 0x5, 0x3, 
       0x6, 0x3, 0x6, 0x7, 0x6, 0x56, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x59, 
       0xb, 0x6, 0x3, 0x6, 0x6, 0x6, 0x5c, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 
       0x5d, 0x6, 0x6, 0x60, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x61, 0x3, 0x6, 
       0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x68, 0xa, 0x7, 0xc, 0x7, 
       0xe, 0x7, 0x6b, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x5, 0x9, 0x72, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x7, 0xa, 0x78, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x7b, 0xb, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x7f, 0xa, 0xa, 0xc, 0xa, 0xe, 
       0xa, 0x82, 0xb, 0xa, 0x5, 0xa, 0x84, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x8a, 0xa, 0xa, 0x3, 0xb, 0x7, 0xb, 
       0x8d, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x90, 0xb, 0xb, 0x3, 0xb, 0x3, 
       0xb, 0x7, 0xb, 0x94, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x97, 0xb, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x9b, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 
       0x9e, 0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xa2, 0xa, 0xb, 0xc, 
       0xb, 0xe, 0xb, 0xa5, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
       0xd, 0x7, 0xd, 0xab, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xae, 0xb, 0xd, 
       0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xb2, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 
       0x29, 0x8e, 0x95, 0x9c, 0xa3, 0x2, 0x11, 0x2, 0x4, 0x6, 0x8, 0xa, 
       0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x2, 0x5, 
       0x5, 0x2, 0x3, 0x3, 0x5, 0x7, 0xa, 0xb, 0x4, 0x2, 0x3, 0x3, 0xb, 
       0xb, 0x3, 0x2, 0x3, 0x4, 0x2, 0xc6, 0x2, 0x21, 0x3, 0x2, 0x2, 0x2, 
       0x4, 0x25, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x8, 
       0x51, 0x3, 0x2, 0x2, 0x2, 0xa, 0x5f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x65, 
       0x3, 0x2, 0x2, 0x2, 0xe, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x10, 0x71, 0x3, 
       0x2, 0x2, 0x2, 0x12, 0x89, 0x3, 0x2, 0x2, 0x2, 0x14, 0x8e, 0x3, 0x2, 
       0x2, 0x2, 0x16, 0xa6, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb1, 0x3, 0x2, 0x2, 
       0x2, 0x1a, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xb6, 0x3, 0x2, 0x2, 0x2, 
       0x1e, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x20, 0x22, 0x5, 0x4, 0x3, 0x2, 0x21, 
       0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x3, 0x2, 0x2, 0x2, 0x23, 0x21, 
       0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 0x3, 0x3, 
       0x2, 0x2, 0x2, 0x25, 0x29, 0x5, 0x1a, 0xe, 0x2, 0x26, 0x28, 0x5, 
       0x1e, 0x10, 0x2, 0x27, 0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2b, 0x3, 
       0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 
       0x2, 0x2, 0x2a, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 
       0x2, 0x2c, 0x2e, 0x5, 0x12, 0xa, 0x2, 0x2d, 0x2c, 0x3, 0x2, 0x2, 
       0x2, 0x2d, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 
       0x2f, 0x3c, 0x5, 0x6, 0x4, 0x2, 0x30, 0x32, 0x7, 0x3, 0x2, 0x2, 0x31, 
       0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x35, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 
       0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x37, 0x3, 
       0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x36, 0x38, 0x7, 0x4, 
       0x2, 0x2, 0x37, 0x36, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 0x2, 0x2, 
       0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x3, 0x2, 0x2, 0x2, 
       0x3a, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3d, 0x7, 0x2, 0x2, 0x3, 0x3c, 
       0x33, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x5, 
       0x3, 0x2, 0x2, 0x2, 0x3e, 0x40, 0x5, 0x1e, 0x10, 0x2, 0x3f, 0x3e, 
       0x3, 0x2, 0x2, 0x2, 0x40, 0x43, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3f, 0x3, 
       0x2, 0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x44, 0x3, 0x2, 
       0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x44, 0x4e, 0x5, 0x1c, 
       0xf, 0x2, 0x45, 0x47, 0x5, 0x1e, 0x10, 0x2, 0x46, 0x45, 0x3, 0x2, 
       0x2, 0x2, 0x47, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 
       0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4b, 0x3, 0x2, 0x2, 0x2, 
       0x4a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4e, 0x5, 0x8, 0x5, 0x2, 0x4c, 
       0x4e, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x41, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x48, 
       0x3, 0x2, 0x2, 0x2, 0x4d, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x7, 0x3, 
       0x2, 0x2, 0x2, 0x4f, 0x52, 0x5, 0xc, 0x7, 0x2, 0x50, 0x52, 0x5, 0xa, 
       0x6, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x50, 0x3, 0x2, 0x2, 
       0x2, 0x52, 0x9, 0x3, 0x2, 0x2, 0x2, 0x53, 0x57, 0x5, 0xc, 0x7, 0x2, 
       0x54, 0x56, 0x7, 0x3, 0x2, 0x2, 0x55, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 
       0x59, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 
       0x3, 0x2, 0x2, 0x2, 0x58, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x59, 0x57, 0x3, 
       0x2, 0x2, 0x2, 0x5a, 0x5c, 0x7, 0x4, 0x2, 0x2, 0x5b, 0x5a, 0x3, 0x2, 
       0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 0x2, 
       0x2, 0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x60, 0x3, 0x2, 0x2, 0x2, 
       0x5f, 0x53, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 
       0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 
       0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x5, 0xc, 0x7, 0x2, 0x64, 0xb, 0x3, 
       0x2, 0x2, 0x2, 0x65, 0x69, 0x5, 0xe, 0x8, 0x2, 0x66, 0x68, 0x5, 0x10, 
       0x9, 0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6b, 0x3, 0x2, 0x2, 
       0x2, 0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 
       0x6a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 
       0x6d, 0x9, 0x2, 0x2, 0x2, 0x6d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x72, 
       0x5, 0xe, 0x8, 0x2, 0x6f, 0x72, 0x7, 0x8, 0x2, 0x2, 0x70, 0x72, 0x7, 
       0x9, 0x2, 0x2, 0x71, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x71, 0x6f, 0x3, 0x2, 
       0x2, 0x2, 0x71, 0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x11, 0x3, 0x2, 0x2, 
       0x2, 0x73, 0x74, 0x7, 0x8, 0x2, 0x2, 0x74, 0x79, 0x5, 0x14, 0xb, 
       0x2, 0x75, 0x76, 0x7, 0x6, 0x2, 0x2, 0x76, 0x78, 0x5, 0x14, 0xb, 
       0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 0x78, 0x7b, 0x3, 0x2, 0x2, 0x2, 
       0x79, 0x77, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 
       0x83, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x80, 
       0x7, 0x6, 0x2, 0x2, 0x7d, 0x7f, 0x5, 0x1e, 0x10, 0x2, 0x7e, 0x7d, 
       0x3, 0x2, 0x2, 0x2, 0x7f, 0x82, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7e, 0x3, 
       0x2, 0x2, 0x2, 0x80, 0x81, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x3, 0x2, 
       0x2, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x83, 0x7c, 0x3, 0x2, 0x2, 
       0x2, 0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 
       0x85, 0x86, 0x7, 0x7, 0x2, 0x2, 0x86, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x87, 
       0x88, 0x7, 0x8, 0x2, 0x2, 0x88, 0x8a, 0x7, 0x7, 0x2, 0x2, 0x89, 0x73, 
       0x3, 0x2, 0x2, 0x2, 0x89, 0x87, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x13, 0x3, 
       0x2, 0x2, 0x2, 0x8b, 0x8d, 0x5, 0x1e, 0x10, 0x2, 0x8c, 0x8b, 0x3, 
       0x2, 0x2, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 
       0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x91, 0x3, 0x2, 0x2, 
       0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x91, 0x95, 0x5, 0x16, 0xc, 
       0x2, 0x92, 0x94, 0x5, 0x1e, 0x10, 0x2, 0x93, 0x92, 0x3, 0x2, 0x2, 
       0x2, 0x94, 0x97, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 
       0x95, 0x93, 0x3, 0x2, 0x2, 0x2, 0x96, 0x98, 0x3, 0x2, 0x2, 0x2, 0x97, 
       0x95, 0x3, 0x2, 0x2, 0x2, 0x98, 0x9c, 0x7, 0x5, 0x2, 0x2, 0x99, 0x9b, 
       0x5, 0x1e, 0x10, 0x2, 0x9a, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9e, 
       0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 
       0x2, 0x2, 0x2, 0x9d, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9c, 0x3, 0x2, 
       0x2, 0x2, 0x9f, 0xa3, 0x5, 0x18, 0xd, 0x2, 0xa0, 0xa2, 0x5, 0x1e, 
       0x10, 0x2, 0xa1, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa5, 0x3, 0x2, 
       0x2, 0x2, 0xa3, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa1, 0x3, 0x2, 0x2, 
       0x2, 0xa4, 0x15, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa3, 0x3, 0x2, 0x2, 0x2, 
       0xa6, 0xa7, 0x7, 0xb, 0x2, 0x2, 0xa7, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa8, 
       0xac, 0x7, 0xb, 0x2, 0x2, 0xa9, 0xab, 0x9, 0x3, 0x2, 0x2, 0xaa, 0xa9, 
       0x3, 0x2, 0x2, 0x2, 0xab, 0xae, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaa, 0x3, 
       0x2, 0x2, 0x2, 0xac, 0xad, 0x3, 0x2, 0x2, 0x2, 0xad, 0xaf, 0x3, 0x2, 
       0x2, 0x2, 0xae, 0xac, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb2, 0x7, 0xb, 0x2, 
       0x2, 0xb0, 0xb2, 0x7, 0xb, 0x2, 0x2, 0xb1, 0xa8, 0x3, 0x2, 0x2, 0x2, 
       0xb1, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x19, 0x3, 0x2, 0x2, 0x2, 0xb3, 
       0xb4, 0x7, 0x9, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0xb, 0x2, 0x2, 0xb5, 0x1b, 
       0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0xc, 0x2, 0x2, 0xb7, 0x1d, 0x3, 
       0x2, 0x2, 0x2, 0xb8, 0xb9, 0x9, 0x4, 0x2, 0x2, 0xb9, 0x1f, 0x3, 0x2, 
       0x2, 0x2, 0x1b, 0x23, 0x29, 0x2d, 0x33, 0x39, 0x3c, 0x41, 0x48, 0x4d, 
       0x51, 0x57, 0x5d, 0x61, 0x69, 0x71, 0x79, 0x80, 0x83, 0x89, 0x8e, 
       0x95, 0x9c, 0xa3, 0xac, 0xb1, 
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
