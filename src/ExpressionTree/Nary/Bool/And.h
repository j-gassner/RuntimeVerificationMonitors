#pragma once

#include "ExpressionTree/Nary/Nary.h"

/**
 * Class representing an And.
 */
class And : public Nary<std::set<std::shared_ptr<Expression>, NaryInterface::SharedPtrExprCompare>, And> {
public:

    /**
     * Constructor.
     * @param expressions Set of expressions connected with and.
     */
    explicit And(const decltype(expressions) &expressions) : Nary(andSymbol, expressions) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;

};



