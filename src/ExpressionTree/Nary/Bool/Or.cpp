#include "Or.h"

std::shared_ptr<Expression> Or::clone() {
    return std::make_shared<Or>(*this);
}

std::shared_ptr<Expression> Or::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitOr(*this, event);
}
