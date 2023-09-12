#pragma once

#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing the previously operator.
 */
class Previously : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit Previously(const std::shared_ptr<Expression> &left) : Unary(
            previousSymbol, left) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override {
        return std::make_shared<Previously>(*this);
    }

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override {
        return visitor.visitPreviously(*this, event);
    }
};



