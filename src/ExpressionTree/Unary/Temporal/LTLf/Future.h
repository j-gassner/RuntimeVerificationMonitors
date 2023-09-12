#pragma once

#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing the future operator.
 */
class Future : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit Future(const std::shared_ptr<Expression> &left) : Unary(
            futureSymbol, left) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override {
        return std::make_shared<Future>(*this);
    }

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override {
        return visitor.visitFuture(*this, event);
    }
};



