
// Generated from /home/fine/CLionProjects/Monitors/src/Parser/Formula.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "FormulaVisitor.h"


/**
 * This class provides an empty implementation of FormulaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class FormulaBaseVisitor : public FormulaVisitor {
public:

    virtual antlrcpp::Any visitFormula(FormulaParser::FormulaContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitEquivalence(FormulaParser::EquivalenceContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitXorExpr(FormulaParser::XorExprContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitImplication(FormulaParser::ImplicationContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitXor(FormulaParser::XorContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitOr(FormulaParser::OrContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAnd(FormulaParser::AndContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitRelease(FormulaParser::ReleaseContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitUntil(FormulaParser::UntilContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitUnaryExpr(FormulaParser::UnaryExprContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitGlobally(FormulaParser::GloballyContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFuture(FormulaParser::FutureContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitOnce(FormulaParser::OnceContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitPreviously(FormulaParser::PreviouslyContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitNextWeak(FormulaParser::NextWeakContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitNextStrong(FormulaParser::NextStrongContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitNot(FormulaParser::NotContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitNotExpr(FormulaParser::NotExprContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAtomExpr(FormulaParser::AtomExprContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitBoolean(FormulaParser::BooleanContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAtomic(FormulaParser::AtomicContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitBrackets(FormulaParser::BracketsContext *ctx) override {
        return visitChildren(ctx);
    }


};

