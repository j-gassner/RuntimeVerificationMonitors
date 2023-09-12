#include "Equivalence.h"

std::shared_ptr<Expression> Equivalence::clone() {
    return std::make_shared<Equivalence>(*this);
}

std::shared_ptr<Expression> Equivalence::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitEquivalence(*this, event);
}
