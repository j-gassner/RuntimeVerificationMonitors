#include "Implication.h"

std::shared_ptr<Expression> Implication::clone() {
    return std::make_shared<Implication>(*this);
}

std::shared_ptr<Expression> Implication::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitImplication(*this, event);
}
