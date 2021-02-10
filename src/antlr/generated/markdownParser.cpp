
// Generated from markdown.g4 by ANTLR 4.9.1


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

std::vector<markdownParser::ListContext *> markdownParser::MarkdownContext::list() {
  return getRuleContexts<markdownParser::ListContext>();
}

markdownParser::ListContext* markdownParser::MarkdownContext::list(size_t i) {
  return getRuleContext<markdownParser::ListContext>(i);
}

std::vector<markdownParser::ParagraphContext *> markdownParser::MarkdownContext::paragraph() {
  return getRuleContexts<markdownParser::ParagraphContext>();
}

markdownParser::ParagraphContext* markdownParser::MarkdownContext::paragraph(size_t i) {
  return getRuleContext<markdownParser::ParagraphContext>(i);
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
    setState(32); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(32);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(30);
        list();
        break;
      }

      case 2: {
        setState(31);
        paragraph();
        break;
      }

      default:
        break;
      }
      setState(34); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__1)
      | (1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__4)
      | (1ULL << markdownParser::T__5)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::T__7)
      | (1ULL << markdownParser::T__8)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
   
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

markdownParser::ItemizeContext* markdownParser::ListContext::itemize() {
  return getRuleContext<markdownParser::ItemizeContext>(0);
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
    setState(38);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::T__1: {
        enterOuterAlt(_localctx, 1);
        setState(36);
        itemize();
        break;
      }

      case markdownParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(37);
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

//----------------- Item_secondContext ------------------------------------------------------------------

markdownParser::Item_secondContext::Item_secondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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
  enterRule(_localctx, 4, markdownParser::RuleItem_second);

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
    match(markdownParser::T__0);
    setState(42);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(41);
      paragraph();
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

//----------------- ItemContext ------------------------------------------------------------------

markdownParser::ItemContext::ItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::Item_secondContext *> markdownParser::ItemContext::item_second() {
  return getRuleContexts<markdownParser::Item_secondContext>();
}

markdownParser::Item_secondContext* markdownParser::ItemContext::item_second(size_t i) {
  return getRuleContext<markdownParser::Item_secondContext>(i);
}

markdownParser::ParagraphContext* markdownParser::ItemContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
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
  enterRule(_localctx, 6, markdownParser::RuleItem);
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
    setState(44);
    match(markdownParser::T__1);
    setState(46);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(45);
      paragraph();
      break;
    }

    default:
      break;
    }
    setState(51);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == markdownParser::T__0) {
      setState(48);
      item_second();
      setState(53);
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

//----------------- ItemizeContext ------------------------------------------------------------------

markdownParser::ItemizeContext::ItemizeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<markdownParser::ItemContext *> markdownParser::ItemizeContext::item() {
  return getRuleContexts<markdownParser::ItemContext>();
}

markdownParser::ItemContext* markdownParser::ItemizeContext::item(size_t i) {
  return getRuleContext<markdownParser::ItemContext>(i);
}


size_t markdownParser::ItemizeContext::getRuleIndex() const {
  return markdownParser::RuleItemize;
}

void markdownParser::ItemizeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItemize(this);
}

void markdownParser::ItemizeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItemize(this);
}

markdownParser::ItemizeContext* markdownParser::itemize() {
  ItemizeContext *_localctx = _tracker.createInstance<ItemizeContext>(_ctx, getState());
  enterRule(_localctx, 8, markdownParser::RuleItemize);

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
    setState(55); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(54);
              item();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(57); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
  enterRule(_localctx, 10, markdownParser::RuleEnumeration);

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
    setState(60); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(59);
              enum_item();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(62); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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

tree::TerminalNode* markdownParser::Enum_itemContext::INT() {
  return getToken(markdownParser::INT, 0);
}

markdownParser::ParagraphContext* markdownParser::Enum_itemContext::paragraph() {
  return getRuleContext<markdownParser::ParagraphContext>(0);
}

std::vector<markdownParser::Enum_item_secondContext *> markdownParser::Enum_itemContext::enum_item_second() {
  return getRuleContexts<markdownParser::Enum_item_secondContext>();
}

markdownParser::Enum_item_secondContext* markdownParser::Enum_itemContext::enum_item_second(size_t i) {
  return getRuleContext<markdownParser::Enum_item_secondContext>(i);
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
    setState(64);
    match(markdownParser::INT);
    setState(65);
    match(markdownParser::T__2);
    setState(68);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(67);
      paragraph();
      break;
    }

    default:
      break;
    }
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == markdownParser::T__3) {
      setState(70);
      enum_item_second();
      setState(75);
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

//----------------- Enum_item_secondContext ------------------------------------------------------------------

markdownParser::Enum_item_secondContext::Enum_item_secondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* markdownParser::Enum_item_secondContext::INT() {
  return getToken(markdownParser::INT, 0);
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
    setState(76);
    match(markdownParser::T__3);
    setState(77);
    match(markdownParser::INT);
    setState(78);
    match(markdownParser::T__2);
    setState(81);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(80);
      paragraph();
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

//----------------- ParagraphContext ------------------------------------------------------------------

markdownParser::ParagraphContext::ParagraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

markdownParser::New_lineContext* markdownParser::ParagraphContext::new_line() {
  return getRuleContext<markdownParser::New_lineContext>(0);
}

tree::TerminalNode* markdownParser::ParagraphContext::EOF() {
  return getToken(markdownParser::EOF, 0);
}

std::vector<markdownParser::Text_plainContext *> markdownParser::ParagraphContext::text_plain() {
  return getRuleContexts<markdownParser::Text_plainContext>();
}

markdownParser::Text_plainContext* markdownParser::ParagraphContext::text_plain(size_t i) {
  return getRuleContext<markdownParser::Text_plainContext>(i);
}

std::vector<markdownParser::Text_decoratedContext *> markdownParser::ParagraphContext::text_decorated() {
  return getRuleContexts<markdownParser::Text_decoratedContext>();
}

markdownParser::Text_decoratedContext* markdownParser::ParagraphContext::text_decorated(size_t i) {
  return getRuleContext<markdownParser::Text_decoratedContext>(i);
}

std::vector<markdownParser::LatexContext *> markdownParser::ParagraphContext::latex() {
  return getRuleContexts<markdownParser::LatexContext>();
}

markdownParser::LatexContext* markdownParser::ParagraphContext::latex(size_t i) {
  return getRuleContext<markdownParser::LatexContext>(i);
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
    setState(86); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(86);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case markdownParser::T__2:
        case markdownParser::T__6:
        case markdownParser::T__7:
        case markdownParser::INT:
        case markdownParser::TEXT: {
          setState(83);
          text_plain();
          break;
        }

        case markdownParser::T__4:
        case markdownParser::T__5: {
          setState(84);
          text_decorated();
          break;
        }

        case markdownParser::T__8: {
          setState(85);
          latex();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(88); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << markdownParser::T__2)
      | (1ULL << markdownParser::T__4)
      | (1ULL << markdownParser::T__5)
      | (1ULL << markdownParser::T__6)
      | (1ULL << markdownParser::T__7)
      | (1ULL << markdownParser::T__8)
      | (1ULL << markdownParser::INT)
      | (1ULL << markdownParser::TEXT))) != 0));
    setState(92);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::T__9: {
        setState(90);
        new_line();
        break;
      }

      case markdownParser::EOF: {
        setState(91);
        match(markdownParser::EOF);
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
    setState(96);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case markdownParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(94);
        text_bold();
        break;
      }

      case markdownParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(95);
        text_italic();
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

std::vector<markdownParser::Text_decoratedContext *> markdownParser::Text_boldContext::text_decorated() {
  return getRuleContexts<markdownParser::Text_decoratedContext>();
}

markdownParser::Text_decoratedContext* markdownParser::Text_boldContext::text_decorated(size_t i) {
  return getRuleContext<markdownParser::Text_decoratedContext>(i);
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
    setState(98);
    match(markdownParser::T__4);
    setState(101); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(101);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case markdownParser::T__2:
                case markdownParser::T__6:
                case markdownParser::T__7:
                case markdownParser::INT:
                case markdownParser::TEXT: {
                  setState(99);
                  text_plain();
                  break;
                }

                case markdownParser::T__4:
                case markdownParser::T__5: {
                  setState(100);
                  text_decorated();
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
      setState(103); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(105);
    match(markdownParser::T__4);
   
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

std::vector<markdownParser::Text_decoratedContext *> markdownParser::Text_italicContext::text_decorated() {
  return getRuleContexts<markdownParser::Text_decoratedContext>();
}

markdownParser::Text_decoratedContext* markdownParser::Text_italicContext::text_decorated(size_t i) {
  return getRuleContext<markdownParser::Text_decoratedContext>(i);
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
  enterRule(_localctx, 22, markdownParser::RuleText_italic);

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
    setState(107);
    match(markdownParser::T__5);
    setState(110); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(110);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case markdownParser::T__2:
                case markdownParser::T__6:
                case markdownParser::T__7:
                case markdownParser::INT:
                case markdownParser::TEXT: {
                  setState(108);
                  text_plain();
                  break;
                }

                case markdownParser::T__4:
                case markdownParser::T__5: {
                  setState(109);
                  text_decorated();
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
      setState(112); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(114);
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
  enterRule(_localctx, 24, markdownParser::RuleText_plain);
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
    setState(117); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(116);
              _la = _input->LA(1);
              if (!((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << markdownParser::T__2)
                | (1ULL << markdownParser::T__6)
                | (1ULL << markdownParser::T__7)
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
      setState(119); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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

markdownParser::Text_plainContext* markdownParser::LatexContext::text_plain() {
  return getRuleContext<markdownParser::Text_plainContext>(0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(markdownParser::T__8);
    setState(122);
    text_plain();
    setState(123);
    match(markdownParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- New_lineContext ------------------------------------------------------------------

markdownParser::New_lineContext::New_lineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t markdownParser::New_lineContext::getRuleIndex() const {
  return markdownParser::RuleNew_line;
}

void markdownParser::New_lineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNew_line(this);
}

void markdownParser::New_lineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<markdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNew_line(this);
}

markdownParser::New_lineContext* markdownParser::new_line() {
  New_lineContext *_localctx = _tracker.createInstance<New_lineContext>(_ctx, getState());
  enterRule(_localctx, 28, markdownParser::RuleNew_line);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(markdownParser::T__9);
   
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
  "markdown", "list", "item_second", "item", "itemize", "enumeration", "enum_item", 
  "enum_item_second", "paragraph", "text_decorated", "text_bold", "text_italic", 
  "text_plain", "latex", "new_line"
};

std::vector<std::string> markdownParser::_literalNames = {
  "", "'    *'", "'*'", "'.'", "'    '", "'**'", "'__'", "'_'", "' '", "'$'", 
  "'\n'"
};

std::vector<std::string> markdownParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "INT", "TEXT"
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

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xe, 0x82, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x23, 
    0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x24, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x29, 
    0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x2d, 0xa, 0x4, 0x3, 0x5, 0x3, 
    0x5, 0x5, 0x5, 0x31, 0xa, 0x5, 0x3, 0x5, 0x7, 0x5, 0x34, 0xa, 0x5, 0xc, 
    0x5, 0xe, 0x5, 0x37, 0xb, 0x5, 0x3, 0x6, 0x6, 0x6, 0x3a, 0xa, 0x6, 0xd, 
    0x6, 0xe, 0x6, 0x3b, 0x3, 0x7, 0x6, 0x7, 0x3f, 0xa, 0x7, 0xd, 0x7, 0xe, 
    0x7, 0x40, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x47, 0xa, 
    0x8, 0x3, 0x8, 0x7, 0x8, 0x4a, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x4d, 0xb, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x54, 
    0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x6, 0xa, 0x59, 0xa, 0xa, 0xd, 
    0xa, 0xe, 0xa, 0x5a, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x5f, 0xa, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x5, 0xb, 0x63, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x6, 0xc, 0x68, 0xa, 0xc, 0xd, 0xc, 0xe, 0xc, 0x69, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x6, 0xd, 0x71, 0xa, 0xd, 0xd, 0xd, 0xe, 
    0xd, 0x72, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x6, 0xe, 0x78, 0xa, 0xe, 0xd, 
    0xe, 0xe, 0xe, 0x79, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x2, 0x2, 0x11, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x2, 0x3, 0x5, 
    0x2, 0x5, 0x5, 0x9, 0xa, 0xd, 0xe, 0x2, 0x87, 0x2, 0x22, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x28, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x2e, 0x3, 0x2, 0x2, 0x2, 0xa, 0x39, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3e, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x42, 0x3, 0x2, 0x2, 0x2, 0x10, 0x4e, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x58, 0x3, 0x2, 0x2, 0x2, 0x14, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x64, 0x3, 0x2, 0x2, 0x2, 0x18, 0x6d, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x77, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x7b, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x20, 0x23, 0x5, 0x4, 0x3, 0x2, 0x21, 
    0x23, 0x5, 0x12, 0xa, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x26, 0x29, 0x5, 0xa, 0x6, 0x2, 0x27, 0x29, 0x5, 0xc, 0x7, 
    0x2, 0x28, 0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x29, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2c, 0x7, 0x3, 0x2, 0x2, 0x2b, 
    0x2d, 0x5, 0x12, 0xa, 0x2, 0x2c, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0x2d, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 0x7, 
    0x4, 0x2, 0x2, 0x2f, 0x31, 0x5, 0x12, 0xa, 0x2, 0x30, 0x2f, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 0x31, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0x32, 0x34, 0x5, 0x6, 0x4, 0x2, 0x33, 0x32, 0x3, 0x2, 0x2, 0x2, 
    0x34, 0x37, 0x3, 0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x9, 0x3, 0x2, 0x2, 0x2, 0x37, 0x35, 
    0x3, 0x2, 0x2, 0x2, 0x38, 0x3a, 0x5, 0x8, 0x5, 0x2, 0x39, 0x38, 0x3, 
    0x2, 0x2, 0x2, 0x3a, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0x3b, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3c, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x3d, 0x3f, 0x5, 0xe, 0x8, 0x2, 0x3e, 0x3d, 0x3, 0x2, 0x2, 0x2, 
    0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x41, 0xd, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 
    0x7, 0xd, 0x2, 0x2, 0x43, 0x44, 0x7, 0x5, 0x2, 0x2, 0x44, 0x46, 0x3, 
    0x2, 0x2, 0x2, 0x45, 0x47, 0x5, 0x12, 0xa, 0x2, 0x46, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x4b, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x4a, 0x5, 0x10, 0x9, 0x2, 0x49, 0x48, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 
    0x4c, 0x3, 0x2, 0x2, 0x2, 0x4c, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x6, 0x2, 0x2, 0x4f, 0x50, 0x7, 
    0xd, 0x2, 0x2, 0x50, 0x51, 0x7, 0x5, 0x2, 0x2, 0x51, 0x53, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x54, 0x5, 0x12, 0xa, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 
    0x2, 0x53, 0x54, 0x3, 0x2, 0x2, 0x2, 0x54, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x55, 0x59, 0x5, 0x1a, 0xe, 0x2, 0x56, 0x59, 0x5, 0x14, 0xb, 0x2, 0x57, 
    0x59, 0x5, 0x1c, 0xf, 0x2, 0x58, 0x55, 0x3, 0x2, 0x2, 0x2, 0x58, 0x56, 
    0x3, 0x2, 0x2, 0x2, 0x58, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 
    0x2, 0x2, 0x2, 0x5a, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 
    0x2, 0x2, 0x5b, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5f, 0x5, 0x1e, 0x10, 
    0x2, 0x5d, 0x5f, 0x7, 0x2, 0x2, 0x3, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 
    0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x13, 0x3, 0x2, 0x2, 0x2, 0x60, 
    0x63, 0x5, 0x16, 0xc, 0x2, 0x61, 0x63, 0x5, 0x18, 0xd, 0x2, 0x62, 0x60, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x64, 0x67, 0x7, 0x7, 0x2, 0x2, 0x65, 0x68, 0x5, 0x1a, 
    0xe, 0x2, 0x66, 0x68, 0x5, 0x14, 0xb, 0x2, 0x67, 0x65, 0x3, 0x2, 0x2, 
    0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x3, 0x2, 0x2, 0x2, 
    0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 
    0x6b, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0x7, 0x2, 0x2, 0x6c, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x6d, 0x70, 0x7, 0x8, 0x2, 0x2, 0x6e, 0x71, 0x5, 
    0x1a, 0xe, 0x2, 0x6f, 0x71, 0x5, 0x14, 0xb, 0x2, 0x70, 0x6e, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 
    0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 
    0x73, 0x74, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x7, 0x8, 0x2, 0x2, 0x75, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x9, 0x2, 0x2, 0x2, 0x77, 0x76, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x7b, 0x7c, 0x7, 0xb, 0x2, 0x2, 0x7c, 0x7d, 0x5, 0x1a, 0xe, 
    0x2, 0x7d, 0x7e, 0x7, 0xb, 0x2, 0x2, 0x7e, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x80, 0x7, 0xc, 0x2, 0x2, 0x80, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x16, 
    0x22, 0x24, 0x28, 0x2c, 0x30, 0x35, 0x3b, 0x40, 0x46, 0x4b, 0x53, 0x58, 
    0x5a, 0x5e, 0x62, 0x67, 0x69, 0x70, 0x72, 0x79, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

markdownParser::Initializer markdownParser::_init;
