#include "And.h"


std::shared_ptr<Expression> And::clone() {
    return std::make_shared<And>(*this);
}

std::shared_ptr<Expression> And::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitAnd(*this, event);
}
