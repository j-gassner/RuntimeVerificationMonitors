#pragma once


#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing the strong next.
 */
class NextStrong : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit NextStrong(const std::shared_ptr<Expression> &left) : Unary(
            nextStrongSymbol, left) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override {
        return std::make_shared<NextStrong>(*this);
    }

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override {
        return visitor.visitNextStrong(*this, event);
    }
};



