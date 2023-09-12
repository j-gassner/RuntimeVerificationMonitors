#pragma once

#include "ExpressionTree/Expression.h"
#include "ExpressionTree/Unary/Unary.h"

/**
 * Functions to transform a formula into its NNF.
 */
namespace NNF {
    /**
     * Resolves patterns like !!a to a.
     * @param expr Expression that has two Not.
     * @return Expression without double negation.
     */
    std::shared_ptr<Expression> removeDoubleNot(const std::shared_ptr<Not> &expr);

    /**
     * Applay de Morgan's rule to an expression.
     * @param expr Expression.
     * @return Expression after de Morgan was applied.
     */
    std::shared_ptr<Expression> applyDeMorgan(const std::shared_ptr<Not> &expr);

    /**
     * Resolves the pattern a -> b to !a | b.
     * @param expr Expression.
     * @return Resolved implication.
     */
    std::shared_ptr<Expression> removeImplication(const std::shared_ptr<Implication> &expr);

    /**
     * Applies rules for a negated temporal operators.
     * @param expr Expression.
     * @return Resolved expression.
     */
    std::shared_ptr<Expression> moveNotTemporal(const std::shared_ptr<Not> &expr);

    /**
     * Transforms Future and Globally into Until and Release.
     * @param expr
     * @return
     */
    std::shared_ptr<Expression> removeFutureAndGlobally(const std::shared_ptr<Unary> &expr);

    /**
     * Moves a negation into the expression.
     * @param expr Expression.
     * @return New expression with negation on the inside.
     */
    std::shared_ptr<Expression> moveNegationInwards(const std::shared_ptr<Not> &expr);

    /**
     * Applies all the above functions to get NNF.
     * @param expr Expression.
     * @return Expression in NNF.
     */
    std::shared_ptr<Expression> evaluate(const std::shared_ptr<Expression> &expr);
}



