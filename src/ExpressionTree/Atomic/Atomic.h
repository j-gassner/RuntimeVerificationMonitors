#pragma once

#include "ExpressionTree/Expression.h"

/**
 * Class representing an atomic proposition.
 */
class Atomic : public Expression {
public:
    /**
     * Constructor.
     * @param symbol Symbol of the Atomic.
     */
    explicit Atomic(std::string symbol) : Expression(std::move(symbol)) {}

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;

};



