#include "Expression.h"

std::string Expression::to_string() const {
    return "";
}

const std::string &Expression::getSymbol() const {
    return symbol;
}

void Expression::setSymbol(const std::string &symb) {
    Expression::symbol = symb;
}

bool operator==(const Expression &e1, const Expression &e2) {
    bool ret = e1.to_string() == e2.to_string();
    return ret;
}

bool operator<(const Expression &e1, const Expression &e2) {
    return e1.to_string() < e2.to_string();
}
//bool Expression::operator==(const Expression &expr) const { return expr.to_string() == this->to_string(); }

bool Expression::isConstTrue() const {
    return to_string() == "true";
}

bool Expression::isConstFalse() const {
    return to_string() == "false";
}

bool Expression::isConst(bool constant) const {
    if (constant) {
        return isConstTrue();
    }
    return isConstFalse();
}

