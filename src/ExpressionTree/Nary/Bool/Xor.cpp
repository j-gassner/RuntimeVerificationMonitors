#include "Xor.h"

std::shared_ptr<Expression> Xor::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitXor(*this, event);
}

std::shared_ptr<Expression> Xor::clone() {
    return std::make_shared<Xor>(*this);
}
