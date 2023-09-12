
// Generated from /home/fine/CLionProjects/Monitors/src/Parser/Formula.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "FormulaParser.h"


/**
 * This class defines an abstract visitor for a parse tree
 * produced by FormulaParser.
 */
class FormulaVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

    /**
     * Visit parse trees produced by FormulaParser.
     */
    virtual antlrcpp::Any visitFormula(FormulaParser::FormulaContext *context) = 0;

    virtual antlrcpp::Any visitEquivalence(FormulaParser::EquivalenceContext *context) = 0;

    virtual antlrcpp::Any visitXorExpr(FormulaParser::XorExprContext *context) = 0;

    virtual antlrcpp::Any visitImplication(FormulaParser::ImplicationContext *context) = 0;

    virtual antlrcpp::Any visitXor(FormulaParser::XorContext *context) = 0;

    virtual antlrcpp::Any visitOr(FormulaParser::OrContext *context) = 0;

    virtual antlrcpp::Any visitAnd(FormulaParser::AndContext *context) = 0;

    virtual antlrcpp::Any visitRelease(FormulaParser::ReleaseContext *context) = 0;

    virtual antlrcpp::Any visitUntil(FormulaParser::UntilContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(FormulaParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitGlobally(FormulaParser::GloballyContext *context) = 0;

    virtual antlrcpp::Any visitFuture(FormulaParser::FutureContext *context) = 0;

    virtual antlrcpp::Any visitOnce(FormulaParser::OnceContext *context) = 0;

    virtual antlrcpp::Any visitPreviously(FormulaParser::PreviouslyContext *context) = 0;

    virtual antlrcpp::Any visitNextWeak(FormulaParser::NextWeakContext *context) = 0;

    virtual antlrcpp::Any visitNextStrong(FormulaParser::NextStrongContext *context) = 0;

    virtual antlrcpp::Any visitNot(FormulaParser::NotContext *context) = 0;

    virtual antlrcpp::Any visitNotExpr(FormulaParser::NotExprContext *context) = 0;

    virtual antlrcpp::Any visitAtomExpr(FormulaParser::AtomExprContext *context) = 0;

    virtual antlrcpp::Any visitBoolean(FormulaParser::BooleanContext *context) = 0;

    virtual antlrcpp::Any visitAtomic(FormulaParser::AtomicContext *context) = 0;

    virtual antlrcpp::Any visitBrackets(FormulaParser::BracketsContext *context) = 0;


};

