#pragma once


#include "Rewriting/ExpressionVisitor.h"
#include "Formula/Formula.h"

/**
 * Visitor applying the eventconsuming rules to a formula and propagating the EventOperator down the expression tree.
 */
class EventConsumingVisitor : public ExpressionVisitor {

public:
    /**
     * Binds a formula and an event to an EventOperator.
     * @param formula Formula.
     * @param event Event.
     */
    void consumeEvent(Formula &formula, Event &event);

    /**
     * Logic for traversing entire expression tree.
     * @param expr Expression.
     * @param event Event.
     */
    //void visitExpression(Expression &expr, Event &event);

    /**
     * Converts op to a shared_ptr.
     * @param op Atomic.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitAtomic(Atomic &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Constant.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitConstant(Constant &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op And.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitAnd(And &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Or.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitOr(Or &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Xor.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitXor(Xor &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Implication.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitImplication(Implication &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Equivalence.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitEquivalence(Equivalence &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Not.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitNot(Not &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Future.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitFuture(Future &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Globally.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitGlobally(Globally &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op NextStrong.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitNextStrong(NextStrong &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op NextWeak.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitNextWeak(NextWeak &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Once.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitOnce(Once &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Previously.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitPreviously(Previously &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Release.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitRelease(Release &op, Event &event) override;

    /**
     * Converts op to a shared_ptr.
     * @param op Until.
     * @param event Event.
     * @return op as a shared_ptr.
     */
    std::shared_ptr<Expression> visitUntil(Until &op, Event &event) override;

    /**
     * Applies event to its child and applies rewriting rules from eventconsuming algorithm.
     * @param op EventOperator.
     * @param event Event.
     * @return Expression transformed according to rewriting rules.
     */
    std::shared_ptr<Expression> visitEventOperator(EventOperator &op, Event &event) override;

};




