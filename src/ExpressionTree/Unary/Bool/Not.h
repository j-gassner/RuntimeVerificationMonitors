#pragma once

#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing a Not.
 */
class Not : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit Not(const std::shared_ptr<Expression> &left) : Unary(
            notSymbol, left) {}

    std::shared_ptr<Expression> clone() override;

    std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;
};



