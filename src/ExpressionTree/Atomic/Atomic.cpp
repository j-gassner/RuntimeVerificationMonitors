#include "Atomic.h"

std::string Atomic::to_string() const {
    return this->getSymbol();
}

std::shared_ptr<Expression> Atomic::clone() {
    return std::make_shared<Atomic>(*this);
}

std::shared_ptr<Expression> Atomic::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitAtomic(*this, event);
}
