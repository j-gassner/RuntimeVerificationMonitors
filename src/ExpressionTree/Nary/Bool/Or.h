#pragma once


#include "ExpressionTree/Nary/Nary.h"

/**
 * Class representing an Or.
 */
class Or : public Nary<std::set<std::shared_ptr<Expression>, NaryInterface::SharedPtrExprCompare>, Or> {
public:
    /**
     * Constructor.
     * @param expressions Set of expressions connected with or.
     */
    explicit Or(const decltype(expressions) &expressions) : Nary(orSymbol, expressions) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;
};


