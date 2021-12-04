
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
    enterOuterAlt(_localctx, 1);
    setState(37);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__0)
      | (1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__3)
      | (1ULL << markdownParser::T__4)
      | (1ULL << markdownParser::T__5)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0)) {
      setState(31);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(28);
        paragraph();
        break;
      }

      case 2: {
        setState(29);
        list();
        break;
      }

      case 3: {
        setState(30);
        latex_next_line();
        break;
      }

      default:
        break;
      }
      setState(33);
      match(markdownParser::T__0);
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(40);
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
    enterOuterAlt(_localctx, 1);
    setState(42);
    itemization();
   
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
    setState(44);
    item();
    setState(49);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(45);
        match(markdownParser::T__0);
        setState(46);
        item(); 
      }
      setState(51);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
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

tree::TerminalNode* markdownParser::Item_secondContext::ITEM_SECOND_INTRO() {
  return getToken(markdownParser::ITEM_SECOND_INTRO, 0);
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
  enterRule(_localctx, 6, markdownParser::RuleItem_second);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(markdownParser::ITEM_SECOND_INTRO);
    setState(53);
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
  enterRule(_localctx, 8, markdownParser::RuleItem);
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
    setState(55);
    match(markdownParser::STAR);
    setState(56);
    match(markdownParser::T__1);
    setState(57);
    paragraph();
    setState(69);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::ENUM_SECOND_INTRO: {
        setState(60); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(59);
          enum_item_second();
          setState(62); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == markdownParser::ENUM_SECOND_INTRO);
        break;
      }

      case markdownParser::ITEM_SECOND_INTRO: {
        setState(65); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(64);
          item_second();
          setState(67); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == markdownParser::ITEM_SECOND_INTRO);
        break;
      }

      case markdownParser::T__0: {
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

tree::TerminalNode* markdownParser::Enum_item_secondContext::ENUM_SECOND_INTRO() {
  return getToken(markdownParser::ENUM_SECOND_INTRO, 0);
}

markdownParser::ParagraphContext* markdownParser::Enum_item_secondContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
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
  enterRule(_localctx, 10, markdownParser::RuleEnum_item_second);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(markdownParser::ENUM_SECOND_INTRO);
    setState(72);
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
  enterRule(_localctx, 12, markdownParser::RuleParagraph);
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
    setState(80);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__3)
      | (1ULL << markdownParser::T__4)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0)) {
      setState(78);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__2:
        case markdownParser::T__3:
        case markdownParser::STAR: {
          setState(74);
          text_decorated();
          break;
        }

        case markdownParser::T__1:
        case markdownParser::T__6:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(75);
          text_plain();
          break;
        }

        case markdownParser::T__4: {
          setState(76);
          latex();
          break;
        }

        case markdownParser::UNDERSCORE: {
          setState(77);
          match(markdownParser::UNDERSCORE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(82);
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
  enterRule(_localctx, 14, markdownParser::RuleText_decorated);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(86);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(83);
        text_bold();
        break;
      }

      case markdownParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(84);
        text_italic();
        break;
      }

      case markdownParser::STAR: {
        enterOuterAlt(_localctx, 3);
        setState(85);
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
  enterRule(_localctx, 16, markdownParser::RuleText_bold);
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
    setState(88);
    match(markdownParser::T__2);
    setState(92); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(92);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__1:
        case markdownParser::T__6:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(89);
          text_plain();
          break;
        }

        case markdownParser::T__3: {
          setState(90);
          text_italic();
          break;
        }

        case markdownParser::STAR: {
          setState(91);
          text_marked();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(94); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__3)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(96);
    match(markdownParser::T__2);
   
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
  enterRule(_localctx, 18, markdownParser::RuleText_marked);
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
    setState(98);
    match(markdownParser::STAR);
    setState(100); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(99);
      text_plain();
      setState(102); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(104);
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
  enterRule(_localctx, 20, markdownParser::RuleText_italic);
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
    match(markdownParser::T__3);
    setState(110); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(110);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__1:
        case markdownParser::T__6:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(107);
          text_plain();
          break;
        }

        case markdownParser::T__2: {
          setState(108);
          text_bold();
          break;
        }

        case markdownParser::STAR: {
          setState(109);
          text_marked();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(112); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(114);
    match(markdownParser::T__3);
   
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
  enterRule(_localctx, 22, markdownParser::RuleLatex);
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
    setState(116);
    match(markdownParser::T__4);
    setState(120); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(120);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__1:
        case markdownParser::T__6:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(117);
          text_plain();
          break;
        }

        case markdownParser::UNDERSCORE: {
          setState(118);
          match(markdownParser::UNDERSCORE);
          break;
        }

        case markdownParser::STAR: {
          setState(119);
          match(markdownParser::STAR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(122); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(124);
    match(markdownParser::T__4);
   
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
  enterRule(_localctx, 24, markdownParser::RuleLatex_next_line);
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
    setState(126);
    match(markdownParser::T__5);
    setState(130); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(130);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__1:
        case markdownParser::T__6:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(127);
          text_plain();
          break;
        }

        case markdownParser::UNDERSCORE: {
          setState(128);
          match(markdownParser::UNDERSCORE);
          break;
        }

        case markdownParser::STAR: {
          setState(129);
          match(markdownParser::STAR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(132); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::UNDERSCORE)
      | (1ULL << markdownParser::STAR)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(134);
    match(markdownParser::T__5);
   
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
  enterRule(_localctx, 26, markdownParser::RuleText_plain);
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
    setState(137); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(136);
              _la = _input->LA(1);
              if (!((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << markdownParser::T__1)
                | (1ULL << markdownParser::T__6)
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
      setState(139); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
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
  "markdown", "list", "itemization", "item_second", "item", "enum_item_second", 
  "paragraph", "text_decorated", "text_bold", "text_marked", "text_italic", 
  "latex", "latex_next_line", "text_plain"
};

std::vector<std::string> markdownParser::_literalNames = {
  "", "'\n'", "' '", "'**'", "'__'", "'$'", "'$$'", "'.'", "", "", "'_'", 
  "'*'"
};

std::vector<std::string> markdownParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "ITEM_SECOND_INTRO", "ENUM_SECOND_INTRO", 
  "UNDERSCORE", "STAR", "INT", "TEXT"
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
       0x3, 0xf, 0x90, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
       0x5, 0x2, 0x22, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x26, 0xa, 
       0x2, 0xc, 0x2, 0xe, 0x2, 0x29, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x32, 0xa, 
       0x4, 0xc, 0x4, 0xe, 0x4, 0x35, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x6, 0x6, 
       0x3f, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x40, 0x3, 0x6, 0x6, 0x6, 0x44, 
       0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x45, 0x5, 0x6, 0x48, 0xa, 0x6, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x7, 0x8, 0x51, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x54, 0xb, 0x8, 0x3, 
       0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x59, 0xa, 0x9, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x6, 0xa, 0x5f, 0xa, 0xa, 0xd, 0xa, 0xe, 
       0xa, 0x60, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0x67, 
       0xa, 0xb, 0xd, 0xb, 0xe, 0xb, 0x68, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
       0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x6, 0xc, 0x71, 0xa, 0xc, 0xd, 0xc, 
       0xe, 0xc, 0x72, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x6, 0xd, 0x7b, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0x7c, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x6, 0xe, 
       0x85, 0xa, 0xe, 0xd, 0xe, 0xe, 0xe, 0x86, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xf, 0x6, 0xf, 0x8c, 0xa, 0xf, 0xd, 0xf, 0xe, 0xf, 0x8d, 0x3, 0xf, 
       0x2, 0x2, 0x10, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
       0x16, 0x18, 0x1a, 0x1c, 0x2, 0x3, 0x5, 0x2, 0x4, 0x4, 0x9, 0x9, 0xe, 
       0xf, 0x2, 0x9d, 0x2, 0x27, 0x3, 0x2, 0x2, 0x2, 0x4, 0x2c, 0x3, 0x2, 
       0x2, 0x2, 0x6, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x36, 0x3, 0x2, 0x2, 
       0x2, 0xa, 0x39, 0x3, 0x2, 0x2, 0x2, 0xc, 0x49, 0x3, 0x2, 0x2, 0x2, 
       0xe, 0x52, 0x3, 0x2, 0x2, 0x2, 0x10, 0x58, 0x3, 0x2, 0x2, 0x2, 0x12, 
       0x5a, 0x3, 0x2, 0x2, 0x2, 0x14, 0x64, 0x3, 0x2, 0x2, 0x2, 0x16, 0x6c, 
       0x3, 0x2, 0x2, 0x2, 0x18, 0x76, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x80, 0x3, 
       0x2, 0x2, 0x2, 0x1c, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x22, 0x5, 0xe, 
       0x8, 0x2, 0x1f, 0x22, 0x5, 0x4, 0x3, 0x2, 0x20, 0x22, 0x5, 0x1a, 
       0xe, 0x2, 0x21, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 0x2, 0x2, 
       0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x3, 0x2, 0x2, 0x2, 
       0x23, 0x24, 0x7, 0x3, 0x2, 0x2, 0x24, 0x26, 0x3, 0x2, 0x2, 0x2, 0x25, 
       0x21, 0x3, 0x2, 0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 
       0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2a, 0x3, 
       0x2, 0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0x2, 
       0x2, 0x3, 0x2b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x5, 0x6, 0x4, 
       0x2, 0x2d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x33, 0x5, 0xa, 0x6, 0x2, 
       0x2f, 0x30, 0x7, 0x3, 0x2, 0x2, 0x30, 0x32, 0x5, 0xa, 0x6, 0x2, 0x31, 
       0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x35, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 
       0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x7, 0x3, 
       0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0xa, 
       0x2, 0x2, 0x37, 0x38, 0x5, 0xe, 0x8, 0x2, 0x38, 0x9, 0x3, 0x2, 0x2, 
       0x2, 0x39, 0x3a, 0x7, 0xd, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0x4, 0x2, 0x2, 
       0x3b, 0x3c, 0x5, 0xe, 0x8, 0x2, 0x3c, 0x47, 0x3, 0x2, 0x2, 0x2, 0x3d, 
       0x3f, 0x5, 0xc, 0x7, 0x2, 0x3e, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 
       0x3, 0x2, 0x2, 0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 
       0x2, 0x2, 0x2, 0x41, 0x48, 0x3, 0x2, 0x2, 0x2, 0x42, 0x44, 0x5, 0x8, 
       0x5, 0x2, 0x43, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x3, 0x2, 0x2, 
       0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 
       0x46, 0x48, 0x3, 0x2, 0x2, 0x2, 0x47, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x47, 
       0x43, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 0xb, 
       0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x7, 0xb, 0x2, 0x2, 0x4a, 0x4b, 0x5, 
       0xe, 0x8, 0x2, 0x4b, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x51, 0x5, 0x10, 
       0x9, 0x2, 0x4d, 0x51, 0x5, 0x1c, 0xf, 0x2, 0x4e, 0x51, 0x5, 0x18, 
       0xd, 0x2, 0x4f, 0x51, 0x7, 0xc, 0x2, 0x2, 0x50, 0x4c, 0x3, 0x2, 0x2, 
       0x2, 0x50, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4e, 0x3, 0x2, 0x2, 0x2, 
       0x50, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x54, 0x3, 0x2, 0x2, 0x2, 0x52, 
       0x50, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 0x53, 0xf, 
       0x3, 0x2, 0x2, 0x2, 0x54, 0x52, 0x3, 0x2, 0x2, 0x2, 0x55, 0x59, 0x5, 
       0x12, 0xa, 0x2, 0x56, 0x59, 0x5, 0x16, 0xc, 0x2, 0x57, 0x59, 0x5, 
       0x14, 0xb, 0x2, 0x58, 0x55, 0x3, 0x2, 0x2, 0x2, 0x58, 0x56, 0x3, 
       0x2, 0x2, 0x2, 0x58, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x11, 0x3, 0x2, 
       0x2, 0x2, 0x5a, 0x5e, 0x7, 0x5, 0x2, 0x2, 0x5b, 0x5f, 0x5, 0x1c, 
       0xf, 0x2, 0x5c, 0x5f, 0x5, 0x16, 0xc, 0x2, 0x5d, 0x5f, 0x5, 0x14, 
       0xb, 0x2, 0x5e, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 
       0x2, 0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x3, 0x2, 0x2, 0x2, 
       0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 
       0x62, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x7, 0x5, 0x2, 0x2, 0x63, 0x13, 
       0x3, 0x2, 0x2, 0x2, 0x64, 0x66, 0x7, 0xd, 0x2, 0x2, 0x65, 0x67, 0x5, 
       0x1c, 0xf, 0x2, 0x66, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 
       0x2, 0x2, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x3, 0x2, 
       0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x7, 0xd, 0x2, 
       0x2, 0x6b, 0x15, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x70, 0x7, 0x6, 0x2, 0x2, 
       0x6d, 0x71, 0x5, 0x1c, 0xf, 0x2, 0x6e, 0x71, 0x5, 0x12, 0xa, 0x2, 
       0x6f, 0x71, 0x5, 0x14, 0xb, 0x2, 0x70, 0x6d, 0x3, 0x2, 0x2, 0x2, 
       0x70, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x70, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 
       0x72, 0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 
       0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x7, 
       0x6, 0x2, 0x2, 0x75, 0x17, 0x3, 0x2, 0x2, 0x2, 0x76, 0x7a, 0x7, 0x7, 
       0x2, 0x2, 0x77, 0x7b, 0x5, 0x1c, 0xf, 0x2, 0x78, 0x7b, 0x7, 0xc, 
       0x2, 0x2, 0x79, 0x7b, 0x7, 0xd, 0x2, 0x2, 0x7a, 0x77, 0x3, 0x2, 0x2, 
       0x2, 0x7a, 0x78, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x79, 0x3, 0x2, 0x2, 0x2, 
       0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7c, 
       0x7d, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 
       0x7, 0x7, 0x2, 0x2, 0x7f, 0x19, 0x3, 0x2, 0x2, 0x2, 0x80, 0x84, 0x7, 
       0x8, 0x2, 0x2, 0x81, 0x85, 0x5, 0x1c, 0xf, 0x2, 0x82, 0x85, 0x7, 
       0xc, 0x2, 0x2, 0x83, 0x85, 0x7, 0xd, 0x2, 0x2, 0x84, 0x81, 0x3, 0x2, 
       0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x84, 0x83, 0x3, 0x2, 0x2, 
       0x2, 0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0x84, 0x3, 0x2, 0x2, 0x2, 
       0x86, 0x87, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 0x2, 0x88, 
       0x89, 0x7, 0x8, 0x2, 0x2, 0x89, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8c, 
       0x9, 0x2, 0x2, 0x2, 0x8b, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x3, 
       0x2, 0x2, 0x2, 0x8d, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x3, 0x2, 
       0x2, 0x2, 0x8e, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x15, 0x21, 0x27, 0x33, 
       0x40, 0x45, 0x47, 0x50, 0x52, 0x58, 0x5e, 0x60, 0x68, 0x70, 0x72, 
       0x7a, 0x7c, 0x84, 0x86, 0x8d, 
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
