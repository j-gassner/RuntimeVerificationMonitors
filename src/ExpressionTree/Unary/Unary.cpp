#include "Unary.h"

std::string Unary::to_string() const {
    return this->getSymbol() + "(" + this->getLeft()->to_string() + ")";
}

const std::shared_ptr<Expression> &Unary::getLeft() const {
    return left;
}

void Unary::setLeft(const std::shared_ptr<Expression> &leftExpr) {
    Unary::left = leftExpr;
}



