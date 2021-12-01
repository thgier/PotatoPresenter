
// Generated from markdown.g4 by ANTLR 4.9.3


#include "markdownListener.h"

#include "markdownParser.h"


using namespace antlrcpp;
using namespace antlr4;

markdownParser::markdownParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

markdownParser::~markdownParser() {
  delete _interpreter;
}

std::string markdownParser::getGrammarFileName() const {
  return "markdown.g4";
}

const std::vector<std::string>& markdownParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& markdownParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- MarkdownContext ------------------------------------------------------------------

markdownParser::MarkdownContext::MarkdownContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* markdownParser::MarkdownContext::EOF() {
  return getToken(markdownParser::EOF, 0);
}

std::vector<markdownParser::ParagraphContext *> markdownParser::MarkdownContext::paragraph() {
  return getRuleContexts<markdownParser::ParagraphContext>();
}

markdownParser::ParagraphContext* markdownParser::MarkdownContext::paragraph(size_t i) {
  return getRuleContext<markdownParser::ParagraphContext>(i);
}

std::vector<markdownParser::ListContext *> markdownParser::MarkdownContext::list() {
  return getRuleContexts<markdownParser::ListContext>();
}

markdownParser::ListContext* markdownParser::MarkdownContext::list(size_t i) {
  return getRuleContext<markdownParser::ListContext>(i);
}

std::vector<markdownParser::Latex_next_lineContext *> markdownParser::MarkdownContext::latex_next_line() {
  return getRuleContexts<markdownParser::Latex_next_lineContext>();
}

markdownParser::Latex_next_lineContext* markdownParser::MarkdownContext::latex_next_line(size_t i) {
  return getRuleContext<markdownParser::Latex_next_lineContext>(i);
}


size_t markdownParser::MarkdownContext::getRuleIndex() const {
  return markdownParser::RuleMarkdown;
}

void markdownParser::MarkdownContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMarkdown(this);
}

void markdownParser::MarkdownContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMarkdown(this);
}

markdownParser::MarkdownContext* markdownParser::markdown() {
  MarkdownContext *_localctx = _tracker.createInstance<MarkdownContext>(_ctx, getState());
  enterRule(_localctx, 0, markdownParser::RuleMarkdown);
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
    setState(41);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(35);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
        case 1: {
          setState(32);
          paragraph();
          break;
        }

        case 2: {
          setState(33);
          list();
          break;
        }

        case 3: {
          setState(34);
          latex_next_line();
          break;
        }

        default:
          break;
        }
        setState(37);
        match(markdownParser::T__0); 
      }
      setState(43);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
    setState(47);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(44);
      paragraph();
      break;
    }

    case 2: {
      setState(45);
      list();
      break;
    }

    case 3: {
      setState(46);
      latex_next_line();
      break;
    }

    default:
      break;
    }
    setState(52);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == markdownParser::T__0) {
      setState(49);
      match(markdownParser::T__0);
      setState(54);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(55);
    match(markdownParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListContext ------------------------------------------------------------------

markdownParser::ListContext::ListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

markdownParser::ItemizationContext* markdownParser::ListContext::itemization() {
  return getRuleContext<markdownParser::ItemizationContext>(0);
}

markdownParser::EnumerationContext* markdownParser::ListContext::enumeration() {
  return getRuleContext<markdownParser::EnumerationContext>(0);
}


size_t markdownParser::ListContext::getRuleIndex() const {
  return markdownParser::RuleList;
}

void markdownParser::ListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterList(this);
}

void markdownParser::ListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitList(this);
}

markdownParser::ListContext* markdownParser::list() {
  ListContext *_localctx = _tracker.createInstance<ListContext>(_ctx, getState());
  enterRule(_localctx, 2, markdownParser::RuleList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(59);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::STAR: {
        enterOuterAlt(_localctx, 1);
        setState(57);
        itemization();
        break;
      }

      case markdownParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(58);
        enumeration();
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

//----------------- ItemizationContext ------------------------------------------------------------------

markdownParser::ItemizationContext::ItemizationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::ItemContext *> markdownParser::ItemizationContext::item() {
  return getRuleContexts<markdownParser::ItemContext>();
}

markdownParser::ItemContext* markdownParser::ItemizationContext::item(size_t i) {
  return getRuleContext<markdownParser::ItemContext>(i);
}


size_t markdownParser::ItemizationContext::getRuleIndex() const {
  return markdownParser::RuleItemization;
}

void markdownParser::ItemizationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItemization(this);
}

void markdownParser::ItemizationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItemization(this);
}

markdownParser::ItemizationContext* markdownParser::itemization() {
  ItemizationContext *_localctx = _tracker.createInstance<ItemizationContext>(_ctx, getState());
  enterRule(_localctx, 4, markdownParser::RuleItemization);

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
    setState(61);
    item();
    setState(66);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(62);
        match(markdownParser::T__0);
        setState(63);
        item(); 
      }
      setState(68);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumerationContext ------------------------------------------------------------------

markdownParser::EnumerationContext::EnumerationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Enum_itemContext *> markdownParser::EnumerationContext::enum_item() {
  return getRuleContexts<markdownParser::Enum_itemContext>();
}

markdownParser::Enum_itemContext* markdownParser::EnumerationContext::enum_item(size_t i) {
  return getRuleContext<markdownParser::Enum_itemContext>(i);
}


size_t markdownParser::EnumerationContext::getRuleIndex() const {
  return markdownParser::RuleEnumeration;
}

void markdownParser::EnumerationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumeration(this);
}

void markdownParser::EnumerationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumeration(this);
}

markdownParser::EnumerationContext* markdownParser::enumeration() {
  EnumerationContext *_localctx = _tracker.createInstance<EnumerationContext>(_ctx, getState());
  enterRule(_localctx, 6, markdownParser::RuleEnumeration);

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
    setState(69);
    enum_item();
    setState(74);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(70);
        match(markdownParser::T__0);
        setState(71);
        enum_item(); 
      }
      setState(76);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Item_secondContext ------------------------------------------------------------------

markdownParser::Item_secondContext::Item_secondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* markdownParser::Item_secondContext::STAR() {
  return getToken(markdownParser::STAR, 0);
}

markdownParser::ParagraphContext* markdownParser::Item_secondContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
}


size_t markdownParser::Item_secondContext::getRuleIndex() const {
  return markdownParser::RuleItem_second;
}

void markdownParser::Item_secondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItem_second(this);
}

void markdownParser::Item_secondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItem_second(this);
}

markdownParser::Item_secondContext* markdownParser::item_second() {
  Item_secondContext *_localctx = _tracker.createInstance<Item_secondContext>(_ctx, getState());
  enterRule(_localctx, 8, markdownParser::RuleItem_second);

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
    match(markdownParser::T__0);
    setState(78);
    match(markdownParser::T__1);
    setState(79);
    match(markdownParser::STAR);
    setState(80);
    paragraph();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ItemContext ------------------------------------------------------------------

markdownParser::ItemContext::ItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* markdownParser::ItemContext::STAR() {
  return getToken(markdownParser::STAR, 0);
}

markdownParser::ParagraphContext* markdownParser::ItemContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
}

std::vector<markdownParser::Enum_item_secondContext *> markdownParser::ItemContext::enum_item_second() {
  return getRuleContexts<markdownParser::Enum_item_secondContext>();
}

markdownParser::Enum_item_secondContext* markdownParser::ItemContext::enum_item_second(size_t i) {
  return getRuleContext<markdownParser::Enum_item_secondContext>(i);
}

std::vector<markdownParser::Item_secondContext *> markdownParser::ItemContext::item_second() {
  return getRuleContexts<markdownParser::Item_secondContext>();
}

markdownParser::Item_secondContext* markdownParser::ItemContext::item_second(size_t i) {
  return getRuleContext<markdownParser::Item_secondContext>(i);
}


size_t markdownParser::ItemContext::getRuleIndex() const {
  return markdownParser::RuleItem;
}

void markdownParser::ItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItem(this);
}

void markdownParser::ItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItem(this);
}

markdownParser::ItemContext* markdownParser::item() {
  ItemContext *_localctx = _tracker.createInstance<ItemContext>(_ctx, getState());
  enterRule(_localctx, 10, markdownParser::RuleItem);

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
    setState(82);
    match(markdownParser::STAR);
    setState(83);
    paragraph();
    setState(97);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(88);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(85);
          enum_item_second(); 
        }
        setState(90);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
      }
      break;
    }

    case 2: {
      setState(94);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(91);
          item_second(); 
        }
        setState(96);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
      }
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

//----------------- Enum_itemContext ------------------------------------------------------------------

markdownParser::Enum_itemContext::Enum_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

markdownParser::ParagraphContext* markdownParser::Enum_itemContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
}

tree::TerminalNode* markdownParser::Enum_itemContext::INT() {
  return getToken(markdownParser::INT, 0);
}

std::vector<markdownParser::Enum_item_secondContext *> markdownParser::Enum_itemContext::enum_item_second() {
  return getRuleContexts<markdownParser::Enum_item_secondContext>();
}

markdownParser::Enum_item_secondContext* markdownParser::Enum_itemContext::enum_item_second(size_t i) {
  return getRuleContext<markdownParser::Enum_item_secondContext>(i);
}

std::vector<markdownParser::Item_secondContext *> markdownParser::Enum_itemContext::item_second() {
  return getRuleContexts<markdownParser::Item_secondContext>();
}

markdownParser::Item_secondContext* markdownParser::Enum_itemContext::item_second(size_t i) {
  return getRuleContext<markdownParser::Item_secondContext>(i);
}


size_t markdownParser::Enum_itemContext::getRuleIndex() const {
  return markdownParser::RuleEnum_item;
}

void markdownParser::Enum_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_item(this);
}

void markdownParser::Enum_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_item(this);
}

markdownParser::Enum_itemContext* markdownParser::enum_item() {
  Enum_itemContext *_localctx = _tracker.createInstance<Enum_itemContext>(_ctx, getState());
  enterRule(_localctx, 12, markdownParser::RuleEnum_item);

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
    match(markdownParser::INT);
    setState(100);
    match(markdownParser::T__2);
    setState(102);
    paragraph();
    setState(115);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(106);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(103);
          enum_item_second(); 
        }
        setState(108);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      }
      break;
    }

    case 2: {
      setState(112);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(109);
          item_second(); 
        }
        setState(114);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
      }
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

//----------------- Enum_item_secondContext ------------------------------------------------------------------

markdownParser::Enum_item_secondContext::Enum_item_secondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

markdownParser::ParagraphContext* markdownParser::Enum_item_secondContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
}

tree::TerminalNode* markdownParser::Enum_item_secondContext::INT() {
  return getToken(markdownParser::INT, 0);
}


size_t markdownParser::Enum_item_secondContext::getRuleIndex() const {
  return markdownParser::RuleEnum_item_second;
}

void markdownParser::Enum_item_secondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_item_second(this);
}

void markdownParser::Enum_item_secondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_item_second(this);
}

markdownParser::Enum_item_secondContext* markdownParser::enum_item_second() {
  Enum_item_secondContext *_localctx = _tracker.createInstance<Enum_item_secondContext>(_ctx, getState());
  enterRule(_localctx, 14, markdownParser::RuleEnum_item_second);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    match(markdownParser::T__0);
    setState(118);
    match(markdownParser::T__1);
    setState(119);
    match(markdownParser::INT);
    setState(120);
    match(markdownParser::T__2);
    setState(122);
    paragraph();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParagraphContext ------------------------------------------------------------------

markdownParser::ParagraphContext::ParagraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Text_decoratedContext *> markdownParser::ParagraphContext::text_decorated() {
  return getRuleContexts<markdownParser::Text_decoratedContext>();
}

markdownParser::Text_decoratedContext* markdownParser::ParagraphContext::text_decorated(size_t i) {
  return getRuleContext<markdownParser::Text_decoratedContext>(i);
}

std::vector<markdownParser::Text_plainContext *> markdownParser::ParagraphContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::ParagraphContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}

std::vector<markdownParser::LatexContext *> markdownParser::ParagraphContext::latex() {
  return getRuleContexts<markdownParser::LatexContext>();
}

markdownParser::LatexContext* markdownParser::ParagraphContext::latex(size_t i) {
  return getRuleContext<markdownParser::LatexContext>(i);
}

std::vector<tree::TerminalNode *> markdownParser::ParagraphContext::UNDERSCORE() {
  return getTokens(markdownParser::UNDERSCORE);
}

tree::TerminalNode* markdownParser::ParagraphContext::UNDERSCORE(size_t i) {
  return getToken(markdownParser::UNDERSCORE, i);
}


size_t markdownParser::ParagraphContext::getRuleIndex() const {
  return markdownParser::RuleParagraph;
}

void markdownParser::ParagraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParagraph(this);
}

void markdownParser::ParagraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParagraph(this);
}

markdownParser::ParagraphContext* markdownParser::paragraph() {
  ParagraphContext *_localctx = _tracker.createInstance<ParagraphContext>(_ctx, getState());
  enterRule(_localctx, 16, markdownParser::RuleParagraph);
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
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__3)
      | (1ULL << markdownParser::T__4)
      | (1ULL << markdownParser::T__5)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0)) {
      setState(128);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__3:
        case markdownParser::T__4:
        case markdownParser::STAR: {
          setState(124);
          text_decorated();
          break;
        }

        case markdownParser::T__2:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(125);
          text_plain();
          break;
        }

        case markdownParser::T__5: {
          setState(126);
          latex();
          break;
        }

        case markdownParser::UNDERSCORE: {
          setState(127);
          match(markdownParser::UNDERSCORE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(132);
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

//----------------- Text_decoratedContext ------------------------------------------------------------------

markdownParser::Text_decoratedContext::Text_decoratedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

markdownParser::Text_boldContext* markdownParser::Text_decoratedContext::text_bold() {
  return getRuleContext<markdownParser::Text_boldContext>(0);
}

markdownParser::Text_italicContext* markdownParser::Text_decoratedContext::text_italic() {
  return getRuleContext<markdownParser::Text_italicContext>(0);
}

markdownParser::Text_markedContext* markdownParser::Text_decoratedContext::text_marked() {
  return getRuleContext<markdownParser::Text_markedContext>(0);
}


size_t markdownParser::Text_decoratedContext::getRuleIndex() const {
  return markdownParser::RuleText_decorated;
}

void markdownParser::Text_decoratedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_decorated(this);
}

void markdownParser::Text_decoratedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_decorated(this);
}

markdownParser::Text_decoratedContext* markdownParser::text_decorated() {
  Text_decoratedContext *_localctx = _tracker.createInstance<Text_decoratedContext>(_ctx, getState());
  enterRule(_localctx, 18, markdownParser::RuleText_decorated);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::T__3: {
        enterOuterAlt(_localctx, 1);
        setState(133);
        text_bold();
        break;
      }

      case markdownParser::T__4: {
        enterOuterAlt(_localctx, 2);
        setState(134);
        text_italic();
        break;
      }

      case markdownParser::STAR: {
        enterOuterAlt(_localctx, 3);
        setState(135);
        text_marked();
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

//----------------- Text_boldContext ------------------------------------------------------------------

markdownParser::Text_boldContext::Text_boldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Text_plainContext *> markdownParser::Text_boldContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::Text_boldContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}

std::vector<markdownParser::Text_italicContext *> markdownParser::Text_boldContext::text_italic() {
  return getRuleContexts<markdownParser::Text_italicContext>();
}

markdownParser::Text_italicContext* markdownParser::Text_boldContext::text_italic(size_t i) {
  return getRuleContext<markdownParser::Text_italicContext>(i);
}

std::vector<markdownParser::Text_markedContext *> markdownParser::Text_boldContext::text_marked() {
  return getRuleContexts<markdownParser::Text_markedContext>();
}

markdownParser::Text_markedContext* markdownParser::Text_boldContext::text_marked(size_t i) {
  return getRuleContext<markdownParser::Text_markedContext>(i);
}


size_t markdownParser::Text_boldContext::getRuleIndex() const {
  return markdownParser::RuleText_bold;
}

void markdownParser::Text_boldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_bold(this);
}

void markdownParser::Text_boldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_bold(this);
}

markdownParser::Text_boldContext* markdownParser::text_bold() {
  Text_boldContext *_localctx = _tracker.createInstance<Text_boldContext>(_ctx, getState());
  enterRule(_localctx, 20, markdownParser::RuleText_bold);
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
    setState(138);
    match(markdownParser::T__3);
    setState(142); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(142);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__2:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(139);
          text_plain();
          break;
        }

        case markdownParser::T__4: {
          setState(140);
          text_italic();
          break;
        }

        case markdownParser::STAR: {
          setState(141);
          text_marked();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(144); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__4)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(146);
    match(markdownParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Text_markedContext ------------------------------------------------------------------

markdownParser::Text_markedContext::Text_markedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> markdownParser::Text_markedContext::STAR() {
  return getTokens(markdownParser::STAR);
}

tree::TerminalNode* markdownParser::Text_markedContext::STAR(size_t i) {
  return getToken(markdownParser::STAR, i);
}

std::vector<markdownParser::Text_plainContext *> markdownParser::Text_markedContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::Text_markedContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}


size_t markdownParser::Text_markedContext::getRuleIndex() const {
  return markdownParser::RuleText_marked;
}

void markdownParser::Text_markedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_marked(this);
}

void markdownParser::Text_markedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_marked(this);
}

markdownParser::Text_markedContext* markdownParser::text_marked() {
  Text_markedContext *_localctx = _tracker.createInstance<Text_markedContext>(_ctx, getState());
  enterRule(_localctx, 22, markdownParser::RuleText_marked);
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
    setState(148);
    match(markdownParser::STAR);
    setState(150); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(149);
      text_plain();
      setState(152); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(154);
    match(markdownParser::STAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Text_italicContext ------------------------------------------------------------------

markdownParser::Text_italicContext::Text_italicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Text_plainContext *> markdownParser::Text_italicContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::Text_italicContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}

std::vector<markdownParser::Text_boldContext *> markdownParser::Text_italicContext::text_bold() {
  return getRuleContexts<markdownParser::Text_boldContext>();
}

markdownParser::Text_boldContext* markdownParser::Text_italicContext::text_bold(size_t i) {
  return getRuleContext<markdownParser::Text_boldContext>(i);
}

std::vector<markdownParser::Text_markedContext *> markdownParser::Text_italicContext::text_marked() {
  return getRuleContexts<markdownParser::Text_markedContext>();
}

markdownParser::Text_markedContext* markdownParser::Text_italicContext::text_marked(size_t i) {
  return getRuleContext<markdownParser::Text_markedContext>(i);
}


size_t markdownParser::Text_italicContext::getRuleIndex() const {
  return markdownParser::RuleText_italic;
}

void markdownParser::Text_italicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_italic(this);
}

void markdownParser::Text_italicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_italic(this);
}

markdownParser::Text_italicContext* markdownParser::text_italic() {
  Text_italicContext *_localctx = _tracker.createInstance<Text_italicContext>(_ctx, getState());
  enterRule(_localctx, 24, markdownParser::RuleText_italic);
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
    setState(156);
    match(markdownParser::T__4);
    setState(160); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(160);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__2:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(157);
          text_plain();
          break;
        }

        case markdownParser::T__3: {
          setState(158);
          text_bold();
          break;
        }

        case markdownParser::STAR: {
          setState(159);
          text_marked();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(162); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__3)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(164);
    match(markdownParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LatexContext ------------------------------------------------------------------

markdownParser::LatexContext::LatexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Text_plainContext *> markdownParser::LatexContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::LatexContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}

std::vector<tree::TerminalNode *> markdownParser::LatexContext::UNDERSCORE() {
  return getTokens(markdownParser::UNDERSCORE);
}

tree::TerminalNode* markdownParser::LatexContext::UNDERSCORE(size_t i) {
  return getToken(markdownParser::UNDERSCORE, i);
}

std::vector<tree::TerminalNode *> markdownParser::LatexContext::STAR() {
  return getTokens(markdownParser::STAR);
}

tree::TerminalNode* markdownParser::LatexContext::STAR(size_t i) {
  return getToken(markdownParser::STAR, i);
}


size_t markdownParser::LatexContext::getRuleIndex() const {
  return markdownParser::RuleLatex;
}

void markdownParser::LatexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLatex(this);
}

void markdownParser::LatexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLatex(this);
}

markdownParser::LatexContext* markdownParser::latex() {
  LatexContext *_localctx = _tracker.createInstance<LatexContext>(_ctx, getState());
  enterRule(_localctx, 26, markdownParser::RuleLatex);
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
    setState(166);
    match(markdownParser::T__5);
    setState(170); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(170);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__2:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(167);
          text_plain();
          break;
        }

        case markdownParser::UNDERSCORE: {
          setState(168);
          match(markdownParser::UNDERSCORE);
          break;
        }

        case markdownParser::STAR: {
          setState(169);
          match(markdownParser::STAR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(172); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(174);
    match(markdownParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Latex_next_lineContext ------------------------------------------------------------------

markdownParser::Latex_next_lineContext::Latex_next_lineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Text_plainContext *> markdownParser::Latex_next_lineContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::Latex_next_lineContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}

std::vector<tree::TerminalNode *> markdownParser::Latex_next_lineContext::UNDERSCORE() {
  return getTokens(markdownParser::UNDERSCORE);
}

tree::TerminalNode* markdownParser::Latex_next_lineContext::UNDERSCORE(size_t i) {
  return getToken(markdownParser::UNDERSCORE, i);
}

std::vector<tree::TerminalNode *> markdownParser::Latex_next_lineContext::STAR() {
  return getTokens(markdownParser::STAR);
}

tree::TerminalNode* markdownParser::Latex_next_lineContext::STAR(size_t i) {
  return getToken(markdownParser::STAR, i);
}


size_t markdownParser::Latex_next_lineContext::getRuleIndex() const {
  return markdownParser::RuleLatex_next_line;
}

void markdownParser::Latex_next_lineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLatex_next_line(this);
}

void markdownParser::Latex_next_lineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLatex_next_line(this);
}

markdownParser::Latex_next_lineContext* markdownParser::latex_next_line() {
  Latex_next_lineContext *_localctx = _tracker.createInstance<Latex_next_lineContext>(_ctx, getState());
  enterRule(_localctx, 28, markdownParser::RuleLatex_next_line);
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
    setState(176);
    match(markdownParser::T__6);
    setState(180); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(180);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__2:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(177);
          text_plain();
          break;
        }

        case markdownParser::UNDERSCORE: {
          setState(178);
          match(markdownParser::UNDERSCORE);
          break;
        }

        case markdownParser::STAR: {
          setState(179);
          match(markdownParser::STAR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(182); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(184);
    match(markdownParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Text_plainContext ------------------------------------------------------------------

markdownParser::Text_plainContext::Text_plainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> markdownParser::Text_plainContext::TEXT() {
  return getTokens(markdownParser::TEXT);
}

tree::TerminalNode* markdownParser::Text_plainContext::TEXT(size_t i) {
  return getToken(markdownParser::TEXT, i);
}

std::vector<tree::TerminalNode *> markdownParser::Text_plainContext::INT() {
  return getTokens(markdownParser::INT);
}

tree::TerminalNode* markdownParser::Text_plainContext::INT(size_t i) {
  return getToken(markdownParser::INT, i);
}


size_t markdownParser::Text_plainContext::getRuleIndex() const {
  return markdownParser::RuleText_plain;
}

void markdownParser::Text_plainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterText_plain(this);
}

void markdownParser::Text_plainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitText_plain(this);
}

markdownParser::Text_plainContext* markdownParser::text_plain() {
  Text_plainContext *_localctx = _tracker.createInstance<Text_plainContext>(_ctx, getState());
  enterRule(_localctx, 30, markdownParser::RuleText_plain);
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
    setState(187); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(186);
              _la = _input->LA(1);
              if (!((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << markdownParser::T__2)
                | (1ULL << markdownParser::INT)
                | (1ULL << markdownParser::TEXT))) != 0))) {
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
      setState(189); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
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
std::vector<dfa::DFA> markdownParser::_decisionToDFA;
atn::PredictionContextCache markdownParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN markdownParser::_atn;
std::vector<uint16_t> markdownParser::_serializedATN;

std::vector<std::string> markdownParser::_ruleNames = {
  "markdown", "list", "itemization", "enumeration", "item_second", "item", 
  "enum_item", "enum_item_second", "paragraph", "text_decorated", "text_bold", 
  "text_marked", "text_italic", "latex", "latex_next_line", "text_plain"
};

std::vector<std::string> markdownParser::_literalNames = {
  "", "'\n'", "'    '", "'.'", "'**'", "'__'", "'$'", "'$$'", "'_'", "'*'"
};

std::vector<std::string> markdownParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "UNDERSCORE", "STAR", "INT", "TEXT"
};

dfa::Vocabulary markdownParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> markdownParser::_tokenNames;

markdownParser::Initializer::Initializer() {
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
       0x3, 0xd, 0xc2, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x26, 0xa, 0x2, 
       0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x2a, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 
       0x2d, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x32, 0xa, 
       0x2, 0x3, 0x2, 0x7, 0x2, 0x35, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x38, 
       0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x3e, 
       0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x43, 0xa, 0x4, 
       0xc, 0x4, 0xe, 0x4, 0x46, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x7, 0x5, 0x4b, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x4e, 0xb, 0x5, 0x3, 
       0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x59, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 
       0x5c, 0xb, 0x7, 0x3, 0x7, 0x7, 0x7, 0x5f, 0xa, 0x7, 0xc, 0x7, 0xe, 
       0x7, 0x62, 0xb, 0x7, 0x5, 0x7, 0x64, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x6b, 0xa, 0x8, 0xc, 0x8, 
       0xe, 0x8, 0x6e, 0xb, 0x8, 0x3, 0x8, 0x7, 0x8, 0x71, 0xa, 0x8, 0xc, 
       0x8, 0xe, 0x8, 0x74, 0xb, 0x8, 0x5, 0x8, 0x76, 0xa, 0x8, 0x3, 0x9, 
       0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x83, 0xa, 0xa, 0xc, 
       0xa, 0xe, 0xa, 0x86, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 
       0xb, 0x8b, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x6, 
       0xc, 0x91, 0xa, 0xc, 0xd, 0xc, 0xe, 0xc, 0x92, 0x3, 0xc, 0x3, 0xc, 
       0x3, 0xd, 0x3, 0xd, 0x6, 0xd, 0x99, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 
       0x9a, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x6, 0xe, 0xa3, 0xa, 0xe, 0xd, 0xe, 0xe, 0xe, 0xa4, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x6, 0xf, 0xad, 0xa, 
       0xf, 0xd, 0xf, 0xe, 0xf, 0xae, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 
       0x10, 0x3, 0x10, 0x3, 0x10, 0x6, 0x10, 0xb7, 0xa, 0x10, 0xd, 0x10, 
       0xe, 0x10, 0xb8, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x6, 0x11, 0xbe, 
       0xa, 0x11, 0xd, 0x11, 0xe, 0x11, 0xbf, 0x3, 0x11, 0x2, 0x2, 0x12, 
       0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
       0x1a, 0x1c, 0x1e, 0x20, 0x2, 0x3, 0x4, 0x2, 0x5, 0x5, 0xc, 0xd, 0x2, 
       0xd4, 0x2, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x4, 0x3d, 0x3, 0x2, 0x2, 0x2, 
       0x6, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x8, 0x47, 0x3, 0x2, 0x2, 0x2, 0xa, 
       0x4f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x54, 0x3, 0x2, 0x2, 0x2, 0xe, 0x65, 
       0x3, 0x2, 0x2, 0x2, 0x10, 0x77, 0x3, 0x2, 0x2, 0x2, 0x12, 0x84, 0x3, 
       0x2, 0x2, 0x2, 0x14, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x16, 0x8c, 0x3, 0x2, 
       0x2, 0x2, 0x18, 0x96, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x9e, 0x3, 0x2, 0x2, 
       0x2, 0x1c, 0xa8, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xb2, 0x3, 0x2, 0x2, 0x2, 
       0x20, 0xbd, 0x3, 0x2, 0x2, 0x2, 0x22, 0x26, 0x5, 0x12, 0xa, 0x2, 
       0x23, 0x26, 0x5, 0x4, 0x3, 0x2, 0x24, 0x26, 0x5, 0x1e, 0x10, 0x2, 
       0x25, 0x22, 0x3, 0x2, 0x2, 0x2, 0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 
       0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 
       0x7, 0x3, 0x2, 0x2, 0x28, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x29, 0x25, 0x3, 
       0x2, 0x2, 0x2, 0x2a, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 
       0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x31, 0x3, 0x2, 0x2, 
       0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x32, 0x5, 0x12, 0xa, 
       0x2, 0x2f, 0x32, 0x5, 0x4, 0x3, 0x2, 0x30, 0x32, 0x5, 0x1e, 0x10, 
       0x2, 0x31, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 
       0x31, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x36, 0x3, 0x2, 0x2, 0x2, 0x33, 
       0x35, 0x7, 0x3, 0x2, 0x2, 0x34, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 0x38, 
       0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 
       0x2, 0x2, 0x2, 0x37, 0x39, 0x3, 0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 
       0x2, 0x2, 0x39, 0x3a, 0x7, 0x2, 0x2, 0x3, 0x3a, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0x3b, 0x3e, 0x5, 0x6, 0x4, 0x2, 0x3c, 0x3e, 0x5, 0x8, 0x5, 0x2, 
       0x3d, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 
       0x5, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x44, 0x5, 0xc, 0x7, 0x2, 0x40, 0x41, 
       0x7, 0x3, 0x2, 0x2, 0x41, 0x43, 0x5, 0xc, 0x7, 0x2, 0x42, 0x40, 0x3, 
       0x2, 0x2, 0x2, 0x43, 0x46, 0x3, 0x2, 0x2, 0x2, 0x44, 0x42, 0x3, 0x2, 
       0x2, 0x2, 0x44, 0x45, 0x3, 0x2, 0x2, 0x2, 0x45, 0x7, 0x3, 0x2, 0x2, 
       0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x47, 0x4c, 0x5, 0xe, 0x8, 0x2, 
       0x48, 0x49, 0x7, 0x3, 0x2, 0x2, 0x49, 0x4b, 0x5, 0xe, 0x8, 0x2, 0x4a, 
       0x48, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4a, 
       0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x9, 0x3, 
       0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x3, 
       0x2, 0x2, 0x50, 0x51, 0x7, 0x4, 0x2, 0x2, 0x51, 0x52, 0x7, 0xb, 0x2, 
       0x2, 0x52, 0x53, 0x5, 0x12, 0xa, 0x2, 0x53, 0xb, 0x3, 0x2, 0x2, 0x2, 
       0x54, 0x55, 0x7, 0xb, 0x2, 0x2, 0x55, 0x56, 0x5, 0x12, 0xa, 0x2, 
       0x56, 0x63, 0x3, 0x2, 0x2, 0x2, 0x57, 0x59, 0x5, 0x10, 0x9, 0x2, 
       0x58, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5a, 
       0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x64, 
       0x3, 0x2, 0x2, 0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5f, 0x5, 
       0xa, 0x6, 0x2, 0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x62, 0x3, 0x2, 
       0x2, 0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 
       0x2, 0x61, 0x64, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 
       0x63, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x63, 0x60, 0x3, 0x2, 0x2, 0x2, 0x64, 
       0xd, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x7, 0xc, 0x2, 0x2, 0x66, 0x67, 
       0x7, 0x5, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 0x2, 0x68, 0x75, 0x5, 
       0x12, 0xa, 0x2, 0x69, 0x6b, 0x5, 0x10, 0x9, 0x2, 0x6a, 0x69, 0x3, 
       0x2, 0x2, 0x2, 0x6b, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 
       0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x76, 0x3, 0x2, 0x2, 
       0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x71, 0x5, 0xa, 0x6, 0x2, 
       0x70, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 0x74, 0x3, 0x2, 0x2, 0x2, 0x72, 
       0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 0x73, 0x76, 
       0x3, 0x2, 0x2, 0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 0x6c, 0x3, 
       0x2, 0x2, 0x2, 0x75, 0x72, 0x3, 0x2, 0x2, 0x2, 0x76, 0xf, 0x3, 0x2, 
       0x2, 0x2, 0x77, 0x78, 0x7, 0x3, 0x2, 0x2, 0x78, 0x79, 0x7, 0x4, 0x2, 
       0x2, 0x79, 0x7a, 0x7, 0xc, 0x2, 0x2, 0x7a, 0x7b, 0x7, 0x5, 0x2, 0x2, 
       0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x5, 0x12, 0xa, 0x2, 
       0x7d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x83, 0x5, 0x14, 0xb, 0x2, 
       0x7f, 0x83, 0x5, 0x20, 0x11, 0x2, 0x80, 0x83, 0x5, 0x1c, 0xf, 0x2, 
       0x81, 0x83, 0x7, 0xa, 0x2, 0x2, 0x82, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x82, 
       0x7f, 0x3, 0x2, 0x2, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x81, 
       0x3, 0x2, 0x2, 0x2, 0x83, 0x86, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 
       0x2, 0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 0x13, 0x3, 0x2, 
       0x2, 0x2, 0x86, 0x84, 0x3, 0x2, 0x2, 0x2, 0x87, 0x8b, 0x5, 0x16, 
       0xc, 0x2, 0x88, 0x8b, 0x5, 0x1a, 0xe, 0x2, 0x89, 0x8b, 0x5, 0x18, 
       0xd, 0x2, 0x8a, 0x87, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 
       0x2, 0x8a, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x15, 0x3, 0x2, 0x2, 0x2, 
       0x8c, 0x90, 0x7, 0x6, 0x2, 0x2, 0x8d, 0x91, 0x5, 0x20, 0x11, 0x2, 
       0x8e, 0x91, 0x5, 0x1a, 0xe, 0x2, 0x8f, 0x91, 0x5, 0x18, 0xd, 0x2, 
       0x90, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 
       0x8f, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 0x90, 
       0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x3, 
       0x2, 0x2, 0x2, 0x94, 0x95, 0x7, 0x6, 0x2, 0x2, 0x95, 0x17, 0x3, 0x2, 
       0x2, 0x2, 0x96, 0x98, 0x7, 0xb, 0x2, 0x2, 0x97, 0x99, 0x5, 0x20, 
       0x11, 0x2, 0x98, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x3, 0x2, 
       0x2, 0x2, 0x9a, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 
       0x2, 0x9b, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0xb, 0x2, 0x2, 
       0x9d, 0x19, 0x3, 0x2, 0x2, 0x2, 0x9e, 0xa2, 0x7, 0x7, 0x2, 0x2, 0x9f, 
       0xa3, 0x5, 0x20, 0x11, 0x2, 0xa0, 0xa3, 0x5, 0x16, 0xc, 0x2, 0xa1, 
       0xa3, 0x5, 0x18, 0xd, 0x2, 0xa2, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa2, 
       0xa0, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 
       0x3, 0x2, 0x2, 0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 
       0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0x7, 
       0x2, 0x2, 0xa7, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xac, 0x7, 0x8, 0x2, 
       0x2, 0xa9, 0xad, 0x5, 0x20, 0x11, 0x2, 0xaa, 0xad, 0x7, 0xa, 0x2, 
       0x2, 0xab, 0xad, 0x7, 0xb, 0x2, 0x2, 0xac, 0xa9, 0x3, 0x2, 0x2, 0x2, 
       0xac, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xac, 0xab, 0x3, 0x2, 0x2, 0x2, 0xad, 
       0xae, 0x3, 0x2, 0x2, 0x2, 0xae, 0xac, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 
       0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x7, 
       0x8, 0x2, 0x2, 0xb1, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb6, 0x7, 0x9, 
       0x2, 0x2, 0xb3, 0xb7, 0x5, 0x20, 0x11, 0x2, 0xb4, 0xb7, 0x7, 0xa, 
       0x2, 0x2, 0xb5, 0xb7, 0x7, 0xb, 0x2, 0x2, 0xb6, 0xb3, 0x3, 0x2, 0x2, 
       0x2, 0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb5, 0x3, 0x2, 0x2, 0x2, 
       0xb7, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xb8, 
       0xb9, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 
       0x7, 0x9, 0x2, 0x2, 0xbb, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbe, 0x9, 
       0x2, 0x2, 0x2, 0xbd, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 
       0x2, 0x2, 0xbf, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x3, 0x2, 0x2, 
       0x2, 0xc0, 0x21, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x25, 0x2b, 0x31, 0x36, 
       0x3d, 0x44, 0x4c, 0x5a, 0x60, 0x63, 0x6c, 0x72, 0x75, 0x82, 0x84, 
       0x8a, 0x90, 0x92, 0x9a, 0xa2, 0xa4, 0xac, 0xae, 0xb6, 0xb8, 0xbf, 
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

markdownParser::Initializer markdownParser::_init;
