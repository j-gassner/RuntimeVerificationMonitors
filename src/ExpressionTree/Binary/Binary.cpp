#include "Binary.h"

const std::shared_ptr<Expression> &Binary::getLeft() const {
    return left;
}

void Binary::setLeft(const std::shared_ptr<Expression> &leftExpr) {
    Binary::left = leftExpr;
}

const std::shared_ptr<Expression> &Binary::getRight() const {
    return right;
}

void Binary::setRight(const std::shared_ptr<Expression> &rightExpr) {
    Binary::right = rightExpr;
}

std::string Binary::to_string() const {
    return "(" + this->getLeft()->to_string() + " " + this->getSymbol() + " " + this->getRight()->to_string() + ")";
}
