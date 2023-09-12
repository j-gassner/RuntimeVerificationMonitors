#pragma once

#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing the Once operator.
 */
class Once : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit Once(const std::shared_ptr<Expression> &left) : Unary(
            onceSymbol, left) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override {
        return std::make_shared<Once>(*this);
    }

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override {
        return visitor.visitOnce(*this, event);
    }
};



