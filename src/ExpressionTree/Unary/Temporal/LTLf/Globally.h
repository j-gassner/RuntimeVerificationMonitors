#pragma once


#include "ExpressionTree/Unary/Unary.h"

/**
 * Class representing the Globally operator.
 */
class Globally : public Unary {
public:
    /**
     * Constructor.
     * @param left Expression.
     */
    explicit Globally(const std::shared_ptr<Expression> &left) : Unary(
            globallySymbol, left) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override {
        return std::make_shared<Globally>(*this);
    }

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override {
        return visitor.visitGlobally(*this, event);
    }
};



