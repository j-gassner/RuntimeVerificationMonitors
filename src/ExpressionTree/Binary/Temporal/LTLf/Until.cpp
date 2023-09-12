#include "Until.h"

std::shared_ptr<Expression> Until::clone() {
    return std::make_shared<Until>(*this);
}

std::shared_ptr<Expression> Until::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitUntil(*this, event);
}
