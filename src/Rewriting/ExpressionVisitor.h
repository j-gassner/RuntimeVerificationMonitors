#pragma once

#include <memory>

class Expression;

class Unary;

class Binary;

class NaryInterface;

class Atomic;

class Constant;

class And;

class Or;

class Xor;

class Implication;

class Not;

class Future;

class Globally;

class NextStrong;

class NextWeak;

class Once;

class Previously;

class Release;

class Until;

class Event;

class EventOperator;

class Equivalence;


/**
 * Parent class to apply the visitor pattern to the expression tree.
 * The functionality of the single visit functions depends on the inheriting class.
 */
class ExpressionVisitor {
public:

    void visitExpression(Expression &expr, Event &event);
    /**
     * Visits an Atomic.
     * @param expr Atomic.
     * @param event Event.
     * @return Transformed Atomic as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitAtomic(Atomic &expr, Event &event) = 0;

    /**
     * Visits an Constant.
     * @param expr Constant.
     * @param event Event.
     * @return Transformed Constant as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitConstant(Constant &expr, Event &event) = 0;

    /**
     * Visits an And.
     * @param expr And.
     * @param event Event.
     * @return Transformed And as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitAnd(And &expr, Event &event) = 0;

    /**
     * Visits an Or.
     * @param expr Or.
     * @param event Event.
     * @return Transformed Or as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitOr(Or &expr, Event &event) = 0;

    /**
     * Visits an Xor.
     * @param expr Xor.
     * @param event Event.
     * @return Transformed Xor as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitXor(Xor &expr, Event &event) = 0;

    /**
     * Visits an Implication.
     * @param expr Implication.
     * @param event Event.
     * @return Transformed Implication as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitImplication(Implication &expr, Event &event) = 0;

    /**
     * Visits an Equivalence.
     * @param expr Equivalence.
     * @param event Event.
     * @return Transformed Equivalence as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitEquivalence(Equivalence &expr, Event &event) = 0;

    /**
     * Visits an Not.
     * @param expr Not.
     * @param event Event.
     * @return Transformed Not as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitNot(Not &expr, Event &event) = 0;

    /**
     * Visits an Future.
     * @param expr Future.
     * @param event Event.
     * @return Transformed Future as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitFuture(Future &expr, Event &event) = 0;

    /**
     * Visits an Globally.
     * @param expr Globally.
     * @param event Event.
     * @return Transformed Globally as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitGlobally(Globally &expr, Event &event) = 0;

    /**
     * Visits an NextStrong.
     * @param expr NextStrong.
     * @param event Event.
     * @return Transformed NextStrong as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitNextStrong(NextStrong &expr, Event &event) = 0;

    /**
     * Visits an NextWeak.
     * @param expr NextWeak.
     * @param event Event.
     * @return Transformed NextWeak as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitNextWeak(NextWeak &expr, Event &event) = 0;

    /**
     * Visits an Once.
     * @param expr Once.
     * @param event Event.
     * @return Transformed Once as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitOnce(Once &expr, Event &event) = 0;

    /**
     * Visits an Previously.
     * @param expr Previously.
     * @param event Event.
     * @return Transformed Previously as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitPreviously(Previously &expr, Event &event) = 0;

    /**
     * Visits an Release.
     * @param expr Release.
     * @param event Event.
     * @return Transformed Release as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitRelease(Release &expr, Event &event) = 0;

    /**
     * Visits an Until.
     * @param expr Until.
     * @param event Event.
     * @return Transformed Until as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitUntil(Until &expr, Event &event) = 0;

    /**
     * Visits an EventOperator.
     * @param expr EventOperator.
     * @param event Event.
     * @return Transformed EventOperator as a shared_ptr.
     */
    virtual std::shared_ptr<Expression> visitEventOperator(EventOperator &expr, Event &event) = 0;

};




