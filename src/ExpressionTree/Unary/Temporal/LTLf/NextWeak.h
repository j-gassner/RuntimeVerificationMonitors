#pragma once


#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing the weak next.
 */
class NextWeak : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit NextWeak(const std::shared_ptr<Expression> &left) : Unary(
            nextWeakSymbol, left) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override {
        return std::make_shared<NextWeak>(*this);
    }

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override {
        return visitor.visitNextWeak(*this, event);
    }
};



