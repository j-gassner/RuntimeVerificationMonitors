
// Generated from /home/fine/CLionProjects/Monitors/src/Parser/Formula.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


class FormulaParser : public antlr4::Parser {
public:
    enum {
        T__0 = 1, T__1 = 2, BOOL = 3, NOT = 4, GLOBALLY = 5, FUTURE = 6, NEXT_WEAK = 7,
        NEXT_STRONG = 8, UNTIL = 9, RELEASE = 10, ONCE = 11, PREVIOUSLY = 12,
        AND = 13, OR = 14, XOR = 15, IMPL = 16, EQ = 17, TRUE = 18, FALSE = 19,
        ATOMIC = 20, WS = 21
    };

    enum {
        RuleFormula = 0, RuleExpr = 1, RuleXor_expr = 2, RuleOr_expr = 3, RuleAnd_expr = 4,
        RuleRelease_until_expr = 5, RuleUnary = 6, RuleAtom = 7
    };

    FormulaParser(antlr4::TokenStream *input);

    ~FormulaParser();

    virtual std::string getGrammarFileName() const override;

    virtual const antlr4::atn::ATN &getATN() const override { return _atn; };

    virtual const std::vector<std::string> &
    getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
    virtual const std::vector<std::string> &getRuleNames() const override;

    virtual antlr4::dfa::Vocabulary &getVocabulary() const override;


    class FormulaContext;

    class ExprContext;

    class Xor_exprContext;

    class Or_exprContext;

    class And_exprContext;

    class Release_until_exprContext;

    class UnaryContext;

    class AtomContext;

    class FormulaContext : public antlr4::ParserRuleContext {
    public:
        FormulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        virtual size_t getRuleIndex() const override;

        ExprContext *expr();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;

    };

    FormulaContext *formula();

    class ExprContext : public antlr4::ParserRuleContext {
    public:
        ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        ExprContext() = default;

        void copyFrom(ExprContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class EquivalenceContext : public ExprContext {
    public:
        EquivalenceContext(ExprContext *ctx);

        FormulaParser::ExprContext *left = nullptr;
        antlr4::Token *op = nullptr;
        FormulaParser::ExprContext *right = nullptr;

        std::vector<ExprContext *> expr();

        ExprContext *expr(size_t i);

        antlr4::tree::TerminalNode *EQ();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class XorExprContext : public ExprContext {
    public:
        XorExprContext(ExprContext *ctx);

        Xor_exprContext *xor_expr();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class ImplicationContext : public ExprContext {
    public:
        ImplicationContext(ExprContext *ctx);

        FormulaParser::ExprContext *left = nullptr;
        antlr4::Token *op = nullptr;
        FormulaParser::ExprContext *right = nullptr;

        std::vector<ExprContext *> expr();

        ExprContext *expr(size_t i);

        antlr4::tree::TerminalNode *IMPL();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    ExprContext *expr();

    ExprContext *expr(int precedence);

    class Xor_exprContext : public antlr4::ParserRuleContext {
    public:
        Xor_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        Xor_exprContext() = default;

        void copyFrom(Xor_exprContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class XorContext : public Xor_exprContext {
    public:
        XorContext(Xor_exprContext *ctx);

        antlr4::Token *op = nullptr;

        std::vector<Or_exprContext *> or_expr();

        Or_exprContext *or_expr(size_t i);

        std::vector<antlr4::tree::TerminalNode *> XOR();

        antlr4::tree::TerminalNode *XOR(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    Xor_exprContext *xor_expr();

    class Or_exprContext : public antlr4::ParserRuleContext {
    public:
        Or_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        Or_exprContext() = default;

        void copyFrom(Or_exprContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class OrContext : public Or_exprContext {
    public:
        OrContext(Or_exprContext *ctx);

        antlr4::Token *op = nullptr;

        std::vector<And_exprContext *> and_expr();

        And_exprContext *and_expr(size_t i);

        std::vector<antlr4::tree::TerminalNode *> OR();

        antlr4::tree::TerminalNode *OR(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    Or_exprContext *or_expr();

    class And_exprContext : public antlr4::ParserRuleContext {
    public:
        And_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        And_exprContext() = default;

        void copyFrom(And_exprContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class AndContext : public And_exprContext {
    public:
        AndContext(And_exprContext *ctx);

        antlr4::Token *op = nullptr;

        std::vector<Release_until_exprContext *> release_until_expr();

        Release_until_exprContext *release_until_expr(size_t i);

        std::vector<antlr4::tree::TerminalNode *> AND();

        antlr4::tree::TerminalNode *AND(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    And_exprContext *and_expr();

    class Release_until_exprContext : public antlr4::ParserRuleContext {
    public:
        Release_until_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        Release_until_exprContext() = default;

        void copyFrom(Release_until_exprContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class UnaryExprContext : public Release_until_exprContext {
    public:
        UnaryExprContext(Release_until_exprContext *ctx);

        UnaryContext *unary();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class ReleaseContext : public Release_until_exprContext {
    public:
        ReleaseContext(Release_until_exprContext *ctx);

        FormulaParser::UnaryContext *left = nullptr;
        antlr4::Token *op = nullptr;
        FormulaParser::UnaryContext *right = nullptr;

        std::vector<UnaryContext *> unary();

        UnaryContext *unary(size_t i);

        antlr4::tree::TerminalNode *RELEASE();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class UntilContext : public Release_until_exprContext {
    public:
        UntilContext(Release_until_exprContext *ctx);

        FormulaParser::UnaryContext *left = nullptr;
        antlr4::Token *op = nullptr;
        FormulaParser::UnaryContext *right = nullptr;

        std::vector<UnaryContext *> unary();

        UnaryContext *unary(size_t i);

        antlr4::tree::TerminalNode *UNTIL();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    Release_until_exprContext *release_until_expr();

    class UnaryContext : public antlr4::ParserRuleContext {
    public:
        UnaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        UnaryContext() = default;

        void copyFrom(UnaryContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class NextStrongContext : public UnaryContext {
    public:
        NextStrongContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *NEXT_STRONG();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class GloballyContext : public UnaryContext {
    public:
        GloballyContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *GLOBALLY();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class NotContext : public UnaryContext {
    public:
        NotContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *NOT();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class OnceContext : public UnaryContext {
    public:
        OnceContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *ONCE();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class PreviouslyContext : public UnaryContext {
    public:
        PreviouslyContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *PREVIOUSLY();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class FutureContext : public UnaryContext {
    public:
        FutureContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *FUTURE();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class NextWeakContext : public UnaryContext {
    public:
        NextWeakContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::AtomContext *right = nullptr;

        antlr4::tree::TerminalNode *NEXT_WEAK();

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class NotExprContext : public UnaryContext {
    public:
        NotExprContext(UnaryContext *ctx);

        antlr4::Token *op = nullptr;
        FormulaParser::ExprContext *right = nullptr;

        antlr4::tree::TerminalNode *NOT();

        ExprContext *expr();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class AtomExprContext : public UnaryContext {
    public:
        AtomExprContext(UnaryContext *ctx);

        AtomContext *atom();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    UnaryContext *unary();

    class AtomContext : public antlr4::ParserRuleContext {
    public:
        AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);

        AtomContext() = default;

        void copyFrom(AtomContext *context);

        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;


    };

    class BracketsContext : public AtomContext {
    public:
        BracketsContext(AtomContext *ctx);

        FormulaParser::ExprContext *content = nullptr;

        std::vector<ExprContext *> expr();

        ExprContext *expr(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class AtomicContext : public AtomContext {
    public:
        AtomicContext(AtomContext *ctx);

        antlr4::tree::TerminalNode *ATOMIC();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    class BooleanContext : public AtomContext {
    public:
        BooleanContext(AtomContext *ctx);

        antlr4::tree::TerminalNode *BOOL();

        virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
    };

    AtomContext *atom();


    virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

    bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

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

