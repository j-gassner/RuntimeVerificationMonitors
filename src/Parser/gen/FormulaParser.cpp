
// Generated from /home/fine/CLionProjects/Monitors/src/Parser/Formula.g4 by ANTLR 4.8


#include "FormulaListener.h"
#include "FormulaVisitor.h"

#include "FormulaParser.h"


using namespace antlrcpp;
using namespace antlr4;

FormulaParser::FormulaParser(TokenStream *input) : Parser(input) {
    _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

FormulaParser::~FormulaParser() {
    delete _interpreter;
}

std::string FormulaParser::getGrammarFileName() const {
    return "Formula.g4";
}

const std::vector<std::string> &FormulaParser::getRuleNames() const {
    return _ruleNames;
}

dfa::Vocabulary &FormulaParser::getVocabulary() const {
    return _vocabulary;
}


//----------------- FormulaContext ------------------------------------------------------------------

FormulaParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

FormulaParser::ExprContext *FormulaParser::FormulaContext::expr() {
    return getRuleContext<FormulaParser::ExprContext>(0);
}


size_t FormulaParser::FormulaContext::getRuleIndex() const {
    return FormulaParser::RuleFormula;
}

void FormulaParser::FormulaContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterFormula(this);
    }
}

void FormulaParser::FormulaContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitFormula(this);
    }
}


antlrcpp::Any FormulaParser::FormulaContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitFormula(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::FormulaContext *FormulaParser::formula() {
    FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
    enterRule(_localctx, 0, FormulaParser::RuleFormula);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(16);
        expr(0);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

FormulaParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::ExprContext::getRuleIndex() const {
    return FormulaParser::RuleExpr;
}

void FormulaParser::ExprContext::copyFrom(ExprContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- EquivalenceContext ------------------------------------------------------------------

std::vector<FormulaParser::ExprContext *> FormulaParser::EquivalenceContext::expr() {
    return getRuleContexts<FormulaParser::ExprContext>();
}

FormulaParser::ExprContext *FormulaParser::EquivalenceContext::expr(size_t i) {
    return getRuleContext<FormulaParser::ExprContext>(i);
}

tree::TerminalNode *FormulaParser::EquivalenceContext::EQ() {
    return getToken(FormulaParser::EQ, 0);
}

FormulaParser::EquivalenceContext::EquivalenceContext(ExprContext *ctx) { copyFrom(ctx); }

void FormulaParser::EquivalenceContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterEquivalence(this);
    }
}

void FormulaParser::EquivalenceContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitEquivalence(this);
    }
}

antlrcpp::Any FormulaParser::EquivalenceContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitEquivalence(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- XorExprContext ------------------------------------------------------------------

FormulaParser::Xor_exprContext *FormulaParser::XorExprContext::xor_expr() {
    return getRuleContext<FormulaParser::Xor_exprContext>(0);
}

FormulaParser::XorExprContext::XorExprContext(ExprContext *ctx) { copyFrom(ctx); }

void FormulaParser::XorExprContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterXorExpr(this);
    }
}

void FormulaParser::XorExprContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitXorExpr(this);
    }
}

antlrcpp::Any FormulaParser::XorExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitXorExpr(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- ImplicationContext ------------------------------------------------------------------

std::vector<FormulaParser::ExprContext *> FormulaParser::ImplicationContext::expr() {
    return getRuleContexts<FormulaParser::ExprContext>();
}

FormulaParser::ExprContext *FormulaParser::ImplicationContext::expr(size_t i) {
    return getRuleContext<FormulaParser::ExprContext>(i);
}

tree::TerminalNode *FormulaParser::ImplicationContext::IMPL() {
    return getToken(FormulaParser::IMPL, 0);
}

FormulaParser::ImplicationContext::ImplicationContext(ExprContext *ctx) { copyFrom(ctx); }

void FormulaParser::ImplicationContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterImplication(this);
    }
}

void FormulaParser::ImplicationContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitImplication(this);
    }
}

antlrcpp::Any FormulaParser::ImplicationContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitImplication(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::ExprContext *FormulaParser::expr() {
    return expr(0);
}

FormulaParser::ExprContext *FormulaParser::expr(int precedence) {
    ParserRuleContext *parentContext = _ctx;
    size_t parentState = getState();
    FormulaParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
    FormulaParser::ExprContext *previousContext = _localctx;
    (void) previousContext; // Silence compiler, in case the context is not used by generated code.
    size_t startState = 2;
    enterRecursionRule(_localctx, 2, FormulaParser::RuleExpr, precedence);


    auto onExit = finally([=] {
        unrollRecursionContexts(parentContext);
    });
    try {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        _localctx = _tracker.createInstance<XorExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(19);
        xor_expr();
        _ctx->stop = _input->LT(-1);
        setState(29);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) {
                    triggerExitRuleEvent();
                }
                previousContext = _localctx;
                setState(27);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
                    case 1: {
                        auto newContext = _tracker.createInstance<ImplicationContext>(
                                _tracker.createInstance<ExprContext>(parentContext, parentState));
                        _localctx = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpr);
                        setState(21);

                        if (!(precpred(_ctx, 3))) { throw FailedPredicateException(this, "precpred(_ctx, 3)"); }
                        setState(22);
                        dynamic_cast<ImplicationContext *>(_localctx)->op = match(FormulaParser::IMPL);
                        setState(23);
                        dynamic_cast<ImplicationContext *>(_localctx)->right = expr(3);
                        break;
                    }

                    case 2: {
                        auto newContext = _tracker.createInstance<EquivalenceContext>(
                                _tracker.createInstance<ExprContext>(parentContext, parentState));
                        _localctx = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpr);
                        setState(24);

                        if (!(precpred(_ctx, 2))) { throw FailedPredicateException(this, "precpred(_ctx, 2)"); }
                        setState(25);
                        dynamic_cast<EquivalenceContext *>(_localctx)->op = match(FormulaParser::EQ);
                        setState(26);
                        dynamic_cast<EquivalenceContext *>(_localctx)->right = expr(2);
                        break;
                    }

                }
            }
            setState(31);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
        }
    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- Xor_exprContext ------------------------------------------------------------------

FormulaParser::Xor_exprContext::Xor_exprContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::Xor_exprContext::getRuleIndex() const {
    return FormulaParser::RuleXor_expr;
}

void FormulaParser::Xor_exprContext::copyFrom(Xor_exprContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- XorContext ------------------------------------------------------------------

std::vector<FormulaParser::Or_exprContext *> FormulaParser::XorContext::or_expr() {
    return getRuleContexts<FormulaParser::Or_exprContext>();
}

FormulaParser::Or_exprContext *FormulaParser::XorContext::or_expr(size_t i) {
    return getRuleContext<FormulaParser::Or_exprContext>(i);
}

std::vector<tree::TerminalNode *> FormulaParser::XorContext::XOR() {
    return getTokens(FormulaParser::XOR);
}

tree::TerminalNode *FormulaParser::XorContext::XOR(size_t i) {
    return getToken(FormulaParser::XOR, i);
}

FormulaParser::XorContext::XorContext(Xor_exprContext *ctx) { copyFrom(ctx); }

void FormulaParser::XorContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterXor(this);
    }
}

void FormulaParser::XorContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitXor(this);
    }
}

antlrcpp::Any FormulaParser::XorContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitXor(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::Xor_exprContext *FormulaParser::xor_expr() {
    Xor_exprContext *_localctx = _tracker.createInstance<Xor_exprContext>(_ctx, getState());
    enterRule(_localctx, 4, FormulaParser::RuleXor_expr);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        size_t alt;
        _localctx = dynamic_cast<Xor_exprContext *>(_tracker.createInstance<FormulaParser::XorContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(32);
        or_expr();
        setState(37);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                setState(33);
                dynamic_cast<XorContext *>(_localctx)->op = match(FormulaParser::XOR);
                setState(34);
                or_expr();
            }
            setState(39);
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

//----------------- Or_exprContext ------------------------------------------------------------------

FormulaParser::Or_exprContext::Or_exprContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::Or_exprContext::getRuleIndex() const {
    return FormulaParser::RuleOr_expr;
}

void FormulaParser::Or_exprContext::copyFrom(Or_exprContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- OrContext ------------------------------------------------------------------

std::vector<FormulaParser::And_exprContext *> FormulaParser::OrContext::and_expr() {
    return getRuleContexts<FormulaParser::And_exprContext>();
}

FormulaParser::And_exprContext *FormulaParser::OrContext::and_expr(size_t i) {
    return getRuleContext<FormulaParser::And_exprContext>(i);
}

std::vector<tree::TerminalNode *> FormulaParser::OrContext::OR() {
    return getTokens(FormulaParser::OR);
}

tree::TerminalNode *FormulaParser::OrContext::OR(size_t i) {
    return getToken(FormulaParser::OR, i);
}

FormulaParser::OrContext::OrContext(Or_exprContext *ctx) { copyFrom(ctx); }

void FormulaParser::OrContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterOr(this);
    }
}

void FormulaParser::OrContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitOr(this);
    }
}

antlrcpp::Any FormulaParser::OrContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitOr(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::Or_exprContext *FormulaParser::or_expr() {
    Or_exprContext *_localctx = _tracker.createInstance<Or_exprContext>(_ctx, getState());
    enterRule(_localctx, 6, FormulaParser::RuleOr_expr);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        size_t alt;
        _localctx = dynamic_cast<Or_exprContext *>(_tracker.createInstance<FormulaParser::OrContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(40);
        and_expr();
        setState(45);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                setState(41);
                dynamic_cast<OrContext *>(_localctx)->op = match(FormulaParser::OR);
                setState(42);
                and_expr();
            }
            setState(47);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- And_exprContext ------------------------------------------------------------------

FormulaParser::And_exprContext::And_exprContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::And_exprContext::getRuleIndex() const {
    return FormulaParser::RuleAnd_expr;
}

void FormulaParser::And_exprContext::copyFrom(And_exprContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- AndContext ------------------------------------------------------------------

std::vector<FormulaParser::Release_until_exprContext *> FormulaParser::AndContext::release_until_expr() {
    return getRuleContexts<FormulaParser::Release_until_exprContext>();
}

FormulaParser::Release_until_exprContext *FormulaParser::AndContext::release_until_expr(size_t i) {
    return getRuleContext<FormulaParser::Release_until_exprContext>(i);
}

std::vector<tree::TerminalNode *> FormulaParser::AndContext::AND() {
    return getTokens(FormulaParser::AND);
}

tree::TerminalNode *FormulaParser::AndContext::AND(size_t i) {
    return getToken(FormulaParser::AND, i);
}

FormulaParser::AndContext::AndContext(And_exprContext *ctx) { copyFrom(ctx); }

void FormulaParser::AndContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterAnd(this);
    }
}

void FormulaParser::AndContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitAnd(this);
    }
}

antlrcpp::Any FormulaParser::AndContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitAnd(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::And_exprContext *FormulaParser::and_expr() {
    And_exprContext *_localctx = _tracker.createInstance<And_exprContext>(_ctx, getState());
    enterRule(_localctx, 8, FormulaParser::RuleAnd_expr);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        size_t alt;
        _localctx = dynamic_cast<And_exprContext *>(_tracker.createInstance<FormulaParser::AndContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(48);
        release_until_expr();
        setState(53);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                setState(49);
                dynamic_cast<AndContext *>(_localctx)->op = match(FormulaParser::AND);
                setState(50);
                release_until_expr();
            }
            setState(55);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Release_until_exprContext ------------------------------------------------------------------

FormulaParser::Release_until_exprContext::Release_until_exprContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::Release_until_exprContext::getRuleIndex() const {
    return FormulaParser::RuleRelease_until_expr;
}

void FormulaParser::Release_until_exprContext::copyFrom(Release_until_exprContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExprContext ------------------------------------------------------------------

FormulaParser::UnaryContext *FormulaParser::UnaryExprContext::unary() {
    return getRuleContext<FormulaParser::UnaryContext>(0);
}

FormulaParser::UnaryExprContext::UnaryExprContext(Release_until_exprContext *ctx) { copyFrom(ctx); }

void FormulaParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterUnaryExpr(this);
    }
}

void FormulaParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitUnaryExpr(this);
    }
}

antlrcpp::Any FormulaParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitUnaryExpr(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- ReleaseContext ------------------------------------------------------------------

std::vector<FormulaParser::UnaryContext *> FormulaParser::ReleaseContext::unary() {
    return getRuleContexts<FormulaParser::UnaryContext>();
}

FormulaParser::UnaryContext *FormulaParser::ReleaseContext::unary(size_t i) {
    return getRuleContext<FormulaParser::UnaryContext>(i);
}

tree::TerminalNode *FormulaParser::ReleaseContext::RELEASE() {
    return getToken(FormulaParser::RELEASE, 0);
}

FormulaParser::ReleaseContext::ReleaseContext(Release_until_exprContext *ctx) { copyFrom(ctx); }

void FormulaParser::ReleaseContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterRelease(this);
    }
}

void FormulaParser::ReleaseContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitRelease(this);
    }
}

antlrcpp::Any FormulaParser::ReleaseContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitRelease(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- UntilContext ------------------------------------------------------------------

std::vector<FormulaParser::UnaryContext *> FormulaParser::UntilContext::unary() {
    return getRuleContexts<FormulaParser::UnaryContext>();
}

FormulaParser::UnaryContext *FormulaParser::UntilContext::unary(size_t i) {
    return getRuleContext<FormulaParser::UnaryContext>(i);
}

tree::TerminalNode *FormulaParser::UntilContext::UNTIL() {
    return getToken(FormulaParser::UNTIL, 0);
}

FormulaParser::UntilContext::UntilContext(Release_until_exprContext *ctx) { copyFrom(ctx); }

void FormulaParser::UntilContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterUntil(this);
    }
}

void FormulaParser::UntilContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitUntil(this);
    }
}

antlrcpp::Any FormulaParser::UntilContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitUntil(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::Release_until_exprContext *FormulaParser::release_until_expr() {
    Release_until_exprContext *_localctx = _tracker.createInstance<Release_until_exprContext>(_ctx, getState());
    enterRule(_localctx, 10, FormulaParser::RuleRelease_until_expr);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(65);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<Release_until_exprContext *>(_tracker.createInstance<FormulaParser::ReleaseContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(56);
                dynamic_cast<ReleaseContext *>(_localctx)->left = unary();
                setState(57);
                dynamic_cast<ReleaseContext *>(_localctx)->op = match(FormulaParser::RELEASE);
                setState(58);
                dynamic_cast<ReleaseContext *>(_localctx)->right = unary();
                break;
            }

            case 2: {
                _localctx = dynamic_cast<Release_until_exprContext *>(_tracker.createInstance<FormulaParser::UntilContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(60);
                dynamic_cast<UntilContext *>(_localctx)->left = unary();
                setState(61);
                dynamic_cast<UntilContext *>(_localctx)->op = match(FormulaParser::UNTIL);
                setState(62);
                dynamic_cast<UntilContext *>(_localctx)->right = unary();
                break;
            }

            case 3: {
                _localctx = dynamic_cast<Release_until_exprContext *>(_tracker.createInstance<FormulaParser::UnaryExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(64);
                unary();
                break;
            }

        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- UnaryContext ------------------------------------------------------------------

FormulaParser::UnaryContext::UnaryContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::UnaryContext::getRuleIndex() const {
    return FormulaParser::RuleUnary;
}

void FormulaParser::UnaryContext::copyFrom(UnaryContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- NextStrongContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::NextStrongContext::NEXT_STRONG() {
    return getToken(FormulaParser::NEXT_STRONG, 0);
}

FormulaParser::AtomContext *FormulaParser::NextStrongContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::NextStrongContext::NextStrongContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::NextStrongContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterNextStrong(this);
    }
}

void FormulaParser::NextStrongContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitNextStrong(this);
    }
}

antlrcpp::Any FormulaParser::NextStrongContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitNextStrong(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- GloballyContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::GloballyContext::GLOBALLY() {
    return getToken(FormulaParser::GLOBALLY, 0);
}

FormulaParser::AtomContext *FormulaParser::GloballyContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::GloballyContext::GloballyContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::GloballyContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterGlobally(this);
    }
}

void FormulaParser::GloballyContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitGlobally(this);
    }
}

antlrcpp::Any FormulaParser::GloballyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitGlobally(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::NotContext::NOT() {
    return getToken(FormulaParser::NOT, 0);
}

FormulaParser::AtomContext *FormulaParser::NotContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::NotContext::NotContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::NotContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterNot(this);
    }
}

void FormulaParser::NotContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitNot(this);
    }
}

antlrcpp::Any FormulaParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitNot(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- OnceContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::OnceContext::ONCE() {
    return getToken(FormulaParser::ONCE, 0);
}

FormulaParser::AtomContext *FormulaParser::OnceContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::OnceContext::OnceContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::OnceContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterOnce(this);
    }
}

void FormulaParser::OnceContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitOnce(this);
    }
}

antlrcpp::Any FormulaParser::OnceContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitOnce(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- PreviouslyContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::PreviouslyContext::PREVIOUSLY() {
    return getToken(FormulaParser::PREVIOUSLY, 0);
}

FormulaParser::AtomContext *FormulaParser::PreviouslyContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::PreviouslyContext::PreviouslyContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::PreviouslyContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterPreviously(this);
    }
}

void FormulaParser::PreviouslyContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitPreviously(this);
    }
}

antlrcpp::Any FormulaParser::PreviouslyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitPreviously(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- FutureContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::FutureContext::FUTURE() {
    return getToken(FormulaParser::FUTURE, 0);
}

FormulaParser::AtomContext *FormulaParser::FutureContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::FutureContext::FutureContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::FutureContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterFuture(this);
    }
}

void FormulaParser::FutureContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitFuture(this);
    }
}

antlrcpp::Any FormulaParser::FutureContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitFuture(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- NextWeakContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::NextWeakContext::NEXT_WEAK() {
    return getToken(FormulaParser::NEXT_WEAK, 0);
}

FormulaParser::AtomContext *FormulaParser::NextWeakContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::NextWeakContext::NextWeakContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::NextWeakContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterNextWeak(this);
    }
}

void FormulaParser::NextWeakContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitNextWeak(this);
    }
}

antlrcpp::Any FormulaParser::NextWeakContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitNextWeak(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- NotExprContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::NotExprContext::NOT() {
    return getToken(FormulaParser::NOT, 0);
}

FormulaParser::ExprContext *FormulaParser::NotExprContext::expr() {
    return getRuleContext<FormulaParser::ExprContext>(0);
}

FormulaParser::NotExprContext::NotExprContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::NotExprContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterNotExpr(this);
    }
}

void FormulaParser::NotExprContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitNotExpr(this);
    }
}

antlrcpp::Any FormulaParser::NotExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitNotExpr(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- AtomExprContext ------------------------------------------------------------------

FormulaParser::AtomContext *FormulaParser::AtomExprContext::atom() {
    return getRuleContext<FormulaParser::AtomContext>(0);
}

FormulaParser::AtomExprContext::AtomExprContext(UnaryContext *ctx) { copyFrom(ctx); }

void FormulaParser::AtomExprContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterAtomExpr(this);
    }
}

void FormulaParser::AtomExprContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitAtomExpr(this);
    }
}

antlrcpp::Any FormulaParser::AtomExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitAtomExpr(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::UnaryContext *FormulaParser::unary() {
    UnaryContext *_localctx = _tracker.createInstance<UnaryContext>(_ctx, getState());
    enterRule(_localctx, 12, FormulaParser::RuleUnary);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(84);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::GloballyContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(67);
                dynamic_cast<GloballyContext *>(_localctx)->op = match(FormulaParser::GLOBALLY);
                setState(68);
                dynamic_cast<GloballyContext *>(_localctx)->right = atom();
                break;
            }

            case 2: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::FutureContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(69);
                dynamic_cast<FutureContext *>(_localctx)->op = match(FormulaParser::FUTURE);
                setState(70);
                dynamic_cast<FutureContext *>(_localctx)->right = atom();
                break;
            }

            case 3: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::OnceContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(71);
                dynamic_cast<OnceContext *>(_localctx)->op = match(FormulaParser::ONCE);
                setState(72);
                dynamic_cast<OnceContext *>(_localctx)->right = atom();
                break;
            }

            case 4: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::PreviouslyContext>(
                        _localctx));
                enterOuterAlt(_localctx, 4);
                setState(73);
                dynamic_cast<PreviouslyContext *>(_localctx)->op = match(FormulaParser::PREVIOUSLY);
                setState(74);
                dynamic_cast<PreviouslyContext *>(_localctx)->right = atom();
                break;
            }

            case 5: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::NextWeakContext>(
                        _localctx));
                enterOuterAlt(_localctx, 5);
                setState(75);
                dynamic_cast<NextWeakContext *>(_localctx)->op = match(FormulaParser::NEXT_WEAK);
                setState(76);
                dynamic_cast<NextWeakContext *>(_localctx)->right = atom();
                break;
            }

            case 6: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::NextStrongContext>(
                        _localctx));
                enterOuterAlt(_localctx, 6);
                setState(77);
                dynamic_cast<NextStrongContext *>(_localctx)->op = match(FormulaParser::NEXT_STRONG);
                setState(78);
                dynamic_cast<NextStrongContext *>(_localctx)->right = atom();
                break;
            }

            case 7: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::NotContext>(_localctx));
                enterOuterAlt(_localctx, 7);
                setState(79);
                dynamic_cast<NotContext *>(_localctx)->op = match(FormulaParser::NOT);
                setState(80);
                dynamic_cast<NotContext *>(_localctx)->right = atom();
                break;
            }

            case 8: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::NotExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 8);
                setState(81);
                dynamic_cast<NotExprContext *>(_localctx)->op = match(FormulaParser::NOT);
                setState(82);
                dynamic_cast<NotExprContext *>(_localctx)->right = expr(0);
                break;
            }

            case 9: {
                _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<FormulaParser::AtomExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 9);
                setState(83);
                atom();
                break;
            }

        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

FormulaParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t FormulaParser::AtomContext::getRuleIndex() const {
    return FormulaParser::RuleAtom;
}

void FormulaParser::AtomContext::copyFrom(AtomContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- BracketsContext ------------------------------------------------------------------

std::vector<FormulaParser::ExprContext *> FormulaParser::BracketsContext::expr() {
    return getRuleContexts<FormulaParser::ExprContext>();
}

FormulaParser::ExprContext *FormulaParser::BracketsContext::expr(size_t i) {
    return getRuleContext<FormulaParser::ExprContext>(i);
}

FormulaParser::BracketsContext::BracketsContext(AtomContext *ctx) { copyFrom(ctx); }

void FormulaParser::BracketsContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterBrackets(this);
    }
}

void FormulaParser::BracketsContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitBrackets(this);
    }
}

antlrcpp::Any FormulaParser::BracketsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitBrackets(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- AtomicContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::AtomicContext::ATOMIC() {
    return getToken(FormulaParser::ATOMIC, 0);
}

FormulaParser::AtomicContext::AtomicContext(AtomContext *ctx) { copyFrom(ctx); }

void FormulaParser::AtomicContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterAtomic(this);
    }
}

void FormulaParser::AtomicContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitAtomic(this);
    }
}

antlrcpp::Any FormulaParser::AtomicContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitAtomic(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}
//----------------- BooleanContext ------------------------------------------------------------------

tree::TerminalNode *FormulaParser::BooleanContext::BOOL() {
    return getToken(FormulaParser::BOOL, 0);
}

FormulaParser::BooleanContext::BooleanContext(AtomContext *ctx) { copyFrom(ctx); }

void FormulaParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->enterBoolean(this);
    }
}

void FormulaParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
    auto parserListener = dynamic_cast<FormulaListener *>(listener);
    if (parserListener != nullptr) {
        parserListener->exitBoolean(this);
    }
}

antlrcpp::Any FormulaParser::BooleanContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<FormulaVisitor *>(visitor)) {
        return parserVisitor->visitBoolean(this);
    }
    else {
        return visitor->visitChildren(this);
    }
}

FormulaParser::AtomContext *FormulaParser::atom() {
    AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
    enterRule(_localctx, 14, FormulaParser::RuleAtom);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(96);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case FormulaParser::BOOL: {
                _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<FormulaParser::BooleanContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(86);
                match(FormulaParser::BOOL);
                break;
            }

            case FormulaParser::ATOMIC: {
                _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<FormulaParser::AtomicContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(87);
                match(FormulaParser::ATOMIC);
                break;
            }

            case FormulaParser::T__0: {
                _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<FormulaParser::BracketsContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(88);
                match(FormulaParser::T__0);
                setState(90);
                _errHandler->sync(this);
                _la = _input->LA(1);
                do {
                    setState(89);
                    dynamic_cast<BracketsContext *>(_localctx)->content = expr(0);
                    setState(92);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                } while ((((_la & ~0x3fULL) == 0) &&
                          ((1ULL << _la) & ((1ULL << FormulaParser::T__0)
                                            | (1ULL << FormulaParser::BOOL)
                                            | (1ULL << FormulaParser::NOT)
                                            | (1ULL << FormulaParser::GLOBALLY)
                                            | (1ULL << FormulaParser::FUTURE)
                                            | (1ULL << FormulaParser::NEXT_WEAK)
                                            | (1ULL << FormulaParser::NEXT_STRONG)
                                            | (1ULL << FormulaParser::ONCE)
                                            | (1ULL << FormulaParser::PREVIOUSLY)
                                            | (1ULL << FormulaParser::ATOMIC))) != 0));
                setState(94);
                match(FormulaParser::T__1);
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

bool FormulaParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
    switch (ruleIndex) {
        case 1:
            return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

        default:
            break;
    }
    return true;
}

bool FormulaParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
    switch (predicateIndex) {
        case 0:
            return precpred(_ctx, 3);
        case 1:
            return precpred(_ctx, 2);

        default:
            break;
    }
    return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> FormulaParser::_decisionToDFA;
atn::PredictionContextCache FormulaParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FormulaParser::_atn;
std::vector<uint16_t> FormulaParser::_serializedATN;

std::vector<std::string> FormulaParser::_ruleNames = {
        "formula", "expr", "xor_expr", "or_expr", "and_expr", "release_until_expr",
        "unary", "atom"
};

std::vector<std::string> FormulaParser::_literalNames = {
        "", "'('", "')'", "", "", "'G'", "'F'", "'W'", "'X'", "'U'", "'R'", "'O'",
        "'P'", "", "", "", "'->'", "'<->'"
};

std::vector<std::string> FormulaParser::_symbolicNames = {
        "", "", "", "BOOL", "NOT", "GLOBALLY", "FUTURE", "NEXT_WEAK", "NEXT_STRONG",
        "UNTIL", "RELEASE", "ONCE", "PREVIOUSLY", "AND", "OR", "XOR", "IMPL",
        "EQ", "TRUE", "FALSE", "ATOMIC", "WS"
};

dfa::Vocabulary FormulaParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> FormulaParser::_tokenNames;

FormulaParser::Initializer::Initializer() {
    for (size_t i = 0; i < _symbolicNames.size(); ++i) {
        std::string name = _vocabulary.getLiteralName(i);
        if (name.empty()) {
            name = _vocabulary.getSymbolicName(i);
        }

        if (name.empty()) {
            _tokenNames.push_back("<INVALID>");
        }
        else {
            _tokenNames.push_back(name);
        }
    }

    _serializedATN = {
            0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964,
            0x3, 0x17, 0x65, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9,
            0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4,
            0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3,
            0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
            0x3, 0x7, 0x3, 0x1e, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x21, 0xb, 0x3, 0x3,
            0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x26, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4,
            0x29, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x2e, 0xa, 0x5,
            0xc, 0x5, 0xe, 0x5, 0x31, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7,
            0x6, 0x36, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x39, 0xb, 0x6, 0x3, 0x7, 0x3,
            0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3,
            0x7, 0x5, 0x7, 0x44, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8,
            0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8,
            0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8,
            0x57, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x6, 0x9, 0x5d,
            0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x5e, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x63,
            0xa, 0x9, 0x3, 0x9, 0x2, 0x3, 0x4, 0xa, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc,
            0xe, 0x10, 0x2, 0x2, 0x2, 0x6e, 0x2, 0x12, 0x3, 0x2, 0x2, 0x2, 0x4,
            0x14, 0x3, 0x2, 0x2, 0x2, 0x6, 0x22, 0x3, 0x2, 0x2, 0x2, 0x8, 0x2a,
            0x3, 0x2, 0x2, 0x2, 0xa, 0x32, 0x3, 0x2, 0x2, 0x2, 0xc, 0x43, 0x3, 0x2,
            0x2, 0x2, 0xe, 0x56, 0x3, 0x2, 0x2, 0x2, 0x10, 0x62, 0x3, 0x2, 0x2,
            0x2, 0x12, 0x13, 0x5, 0x4, 0x3, 0x2, 0x13, 0x3, 0x3, 0x2, 0x2, 0x2,
            0x14, 0x15, 0x8, 0x3, 0x1, 0x2, 0x15, 0x16, 0x5, 0x6, 0x4, 0x2, 0x16,
            0x1f, 0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 0xc, 0x5, 0x2, 0x2, 0x18, 0x19,
            0x7, 0x12, 0x2, 0x2, 0x19, 0x1e, 0x5, 0x4, 0x3, 0x5, 0x1a, 0x1b, 0xc,
            0x4, 0x2, 0x2, 0x1b, 0x1c, 0x7, 0x13, 0x2, 0x2, 0x1c, 0x1e, 0x5, 0x4,
            0x3, 0x4, 0x1d, 0x17, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1a, 0x3, 0x2, 0x2,
            0x2, 0x1e, 0x21, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2,
            0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x5, 0x3, 0x2, 0x2, 0x2, 0x21,
            0x1f, 0x3, 0x2, 0x2, 0x2, 0x22, 0x27, 0x5, 0x8, 0x5, 0x2, 0x23, 0x24,
            0x7, 0x11, 0x2, 0x2, 0x24, 0x26, 0x5, 0x8, 0x5, 0x2, 0x25, 0x23, 0x3,
            0x2, 0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 0x3, 0x2,
            0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x7, 0x3, 0x2, 0x2,
            0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2f, 0x5, 0xa, 0x6, 0x2,
            0x2b, 0x2c, 0x7, 0x10, 0x2, 0x2, 0x2c, 0x2e, 0x5, 0xa, 0x6, 0x2, 0x2d,
            0x2b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x31, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d,
            0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 0x30, 0x9, 0x3,
            0x2, 0x2, 0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x37, 0x5, 0xc,
            0x7, 0x2, 0x33, 0x34, 0x7, 0xf, 0x2, 0x2, 0x34, 0x36, 0x5, 0xc, 0x7,
            0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x36, 0x39, 0x3, 0x2, 0x2, 0x2,
            0x37, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38,
            0xb, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b,
            0x5, 0xe, 0x8, 0x2, 0x3b, 0x3c, 0x7, 0xc, 0x2, 0x2, 0x3c, 0x3d, 0x5,
            0xe, 0x8, 0x2, 0x3d, 0x44, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0xe,
            0x8, 0x2, 0x3f, 0x40, 0x7, 0xb, 0x2, 0x2, 0x40, 0x41, 0x5, 0xe, 0x8,
            0x2, 0x41, 0x44, 0x3, 0x2, 0x2, 0x2, 0x42, 0x44, 0x5, 0xe, 0x8, 0x2,
            0x43, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x43, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x43,
            0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0xd, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46,
            0x7, 0x7, 0x2, 0x2, 0x46, 0x57, 0x5, 0x10, 0x9, 0x2, 0x47, 0x48, 0x7,
            0x8, 0x2, 0x2, 0x48, 0x57, 0x5, 0x10, 0x9, 0x2, 0x49, 0x4a, 0x7, 0xd,
            0x2, 0x2, 0x4a, 0x57, 0x5, 0x10, 0x9, 0x2, 0x4b, 0x4c, 0x7, 0xe, 0x2,
            0x2, 0x4c, 0x57, 0x5, 0x10, 0x9, 0x2, 0x4d, 0x4e, 0x7, 0x9, 0x2, 0x2,
            0x4e, 0x57, 0x5, 0x10, 0x9, 0x2, 0x4f, 0x50, 0x7, 0xa, 0x2, 0x2, 0x50,
            0x57, 0x5, 0x10, 0x9, 0x2, 0x51, 0x52, 0x7, 0x6, 0x2, 0x2, 0x52, 0x57,
            0x5, 0x10, 0x9, 0x2, 0x53, 0x54, 0x7, 0x6, 0x2, 0x2, 0x54, 0x57, 0x5,
            0x4, 0x3, 0x2, 0x55, 0x57, 0x5, 0x10, 0x9, 0x2, 0x56, 0x45, 0x3, 0x2,
            0x2, 0x2, 0x56, 0x47, 0x3, 0x2, 0x2, 0x2, 0x56, 0x49, 0x3, 0x2, 0x2,
            0x2, 0x56, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x56, 0x4d, 0x3, 0x2, 0x2, 0x2,
            0x56, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x56, 0x51, 0x3, 0x2, 0x2, 0x2, 0x56,
            0x53, 0x3, 0x2, 0x2, 0x2, 0x56, 0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0xf,
            0x3, 0x2, 0x2, 0x2, 0x58, 0x63, 0x7, 0x5, 0x2, 0x2, 0x59, 0x63, 0x7,
            0x16, 0x2, 0x2, 0x5a, 0x5c, 0x7, 0x3, 0x2, 0x2, 0x5b, 0x5d, 0x5, 0x4,
            0x3, 0x2, 0x5c, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x3, 0x2, 0x2,
            0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x3, 0x2, 0x2, 0x2,
            0x5f, 0x60, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x7, 0x4, 0x2, 0x2, 0x61,
            0x63, 0x3, 0x2, 0x2, 0x2, 0x62, 0x58, 0x3, 0x2, 0x2, 0x2, 0x62, 0x59,
            0x3, 0x2, 0x2, 0x2, 0x62, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x63, 0x11, 0x3,
            0x2, 0x2, 0x2, 0xb, 0x1d, 0x1f, 0x27, 0x2f, 0x37, 0x43, 0x56, 0x5e,
            0x62,
    };

    atn::ATNDeserializer deserializer;
    _atn = deserializer.deserialize(_serializedATN);

    size_t count = _atn.getNumberOfDecisions();
    _decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++) {
        _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
    }
}

FormulaParser::Initializer FormulaParser::_init;
