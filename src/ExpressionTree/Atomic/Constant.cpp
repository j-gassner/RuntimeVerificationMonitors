#include "Constant.h"

std::string Constant::to_string() const {
    return this->getSymbol();
}

std::shared_ptr<Expression> Constant::clone() {
    return std::make_shared<Constant>(*this);
}

std::shared_ptr<Expression> Constant::accept(ExpressionVisitor &visitor, Event &event) {
    return visitor.visitConstant(*this, event);
}

bool Constant::getValue() const {
    return value;
}
