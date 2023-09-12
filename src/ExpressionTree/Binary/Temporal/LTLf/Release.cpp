#include "Release.h"

std::shared_ptr<Expression> Release::clone() {
    return std::make_shared<Release>(*this);
}

std::shared_ptr<Expression> Release::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitRelease(*this, event);
}
