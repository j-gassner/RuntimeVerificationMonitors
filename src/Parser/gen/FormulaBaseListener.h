
// Generated from /home/fine/CLionProjects/Monitors/src/Parser/Formula.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "FormulaListener.h"


/**
 * This class provides an empty implementation of FormulaListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class FormulaBaseListener : public FormulaListener {
public:

    virtual void enterFormula(FormulaParser::FormulaContext * /*ctx*/) override {}

    virtual void exitFormula(FormulaParser::FormulaContext * /*ctx*/) override {}

    virtual void enterEquivalence(FormulaParser::EquivalenceContext * /*ctx*/) override {}

    virtual void exitEquivalence(FormulaParser::EquivalenceContext * /*ctx*/) override {}

    virtual void enterXorExpr(FormulaParser::XorExprContext * /*ctx*/) override {}

    virtual void exitXorExpr(FormulaParser::XorExprContext * /*ctx*/) override {}

    virtual void enterImplication(FormulaParser::ImplicationContext * /*ctx*/) override {}

    virtual void exitImplication(FormulaParser::ImplicationContext * /*ctx*/) override {}

    virtual void enterXor(FormulaParser::XorContext * /*ctx*/) override {}

    virtual void exitXor(FormulaParser::XorContext * /*ctx*/) override {}

    virtual void enterOr(FormulaParser::OrContext * /*ctx*/) override {}

    virtual void exitOr(FormulaParser::OrContext * /*ctx*/) override {}

    virtual void enterAnd(FormulaParser::AndContext * /*ctx*/) override {}

    virtual void exitAnd(FormulaParser::AndContext * /*ctx*/) override {}

    virtual void enterRelease(FormulaParser::ReleaseContext * /*ctx*/) override {}

    virtual void exitRelease(FormulaParser::ReleaseContext * /*ctx*/) override {}

    virtual void enterUntil(FormulaParser::UntilContext * /*ctx*/) override {}

    virtual void exitUntil(FormulaParser::UntilContext * /*ctx*/) override {}

    virtual void enterUnaryExpr(FormulaParser::UnaryExprContext * /*ctx*/) override {}

    virtual void exitUnaryExpr(FormulaParser::UnaryExprContext * /*ctx*/) override {}

    virtual void enterGlobally(FormulaParser::GloballyContext * /*ctx*/) override {}

    virtual void exitGlobally(FormulaParser::GloballyContext * /*ctx*/) override {}

    virtual void enterFuture(FormulaParser::FutureContext * /*ctx*/) override {}

    virtual void exitFuture(FormulaParser::FutureContext * /*ctx*/) override {}

    virtual void enterOnce(FormulaParser::OnceContext * /*ctx*/) override {}

    virtual void exitOnce(FormulaParser::OnceContext * /*ctx*/) override {}

    virtual void enterPreviously(FormulaParser::PreviouslyContext * /*ctx*/) override {}

    virtual void exitPreviously(FormulaParser::PreviouslyContext * /*ctx*/) override {}

    virtual void enterNextWeak(FormulaParser::NextWeakContext * /*ctx*/) override {}

    virtual void exitNextWeak(FormulaParser::NextWeakContext * /*ctx*/) override {}

    virtual void enterNextStrong(FormulaParser::NextStrongContext * /*ctx*/) override {}

    virtual void exitNextStrong(FormulaParser::NextStrongContext * /*ctx*/) override {}

    virtual void enterNot(FormulaParser::NotContext * /*ctx*/) override {}

    virtual void exitNot(FormulaParser::NotContext * /*ctx*/) override {}

    virtual void enterNotExpr(FormulaParser::NotExprContext * /*ctx*/) override {}

    virtual void exitNotExpr(FormulaParser::NotExprContext * /*ctx*/) override {}

    virtual void enterAtomExpr(FormulaParser::AtomExprContext * /*ctx*/) override {}

    virtual void exitAtomExpr(FormulaParser::AtomExprContext * /*ctx*/) override {}

    virtual void enterBoolean(FormulaParser::BooleanContext * /*ctx*/) override {}

    virtual void exitBoolean(FormulaParser::BooleanContext * /*ctx*/) override {}

    virtual void enterAtomic(FormulaParser::AtomicContext * /*ctx*/) override {}

    virtual void exitAtomic(FormulaParser::AtomicContext * /*ctx*/) override {}

    virtual void enterBrackets(FormulaParser::BracketsContext * /*ctx*/) override {}

    virtual void exitBrackets(FormulaParser::BracketsContext * /*ctx*/) override {}


    virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}

    virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}

    virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override {}

    virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override {}

};

