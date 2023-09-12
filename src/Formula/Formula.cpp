#include "Formula.h"

#include <utility>
#include "Utils/Utils.h"
#include "ExpressionTree/Nary/NaryInterface.h"
#include "ExpressionTree/Binary/Binary.h"
#include "ExpressionTree/Nary/Bool/Xor.h"
#include "NNF.h"

void Formula::toNnf() {
    auto before = deepCopy(expr);
    expr = NNF::evaluate(expr);
    while (!sameTree(before, expr)) {
        before = deepCopy(expr);
        expr = NNF::evaluate(before);
    }
}

[[nodiscard]] std::shared_ptr<Expression> Formula::getExpr() const {
    return expr;
}

void Formula::setExpr(const std::shared_ptr<Expression> &expression) {
    expr = expression;
}

const std::shared_ptr<Event> &Formula::getEvent() const {
    return event;
}

void Formula::setEvent(std::shared_ptr<Event> ev) {
    event = std::move(ev);
}

[[nodiscard]] bool
Formula::sameTree(const std::shared_ptr<Expression> &before, const std::shared_ptr<Expression> &after) {
    return before->to_string() == after->to_string();
}

[[nodiscard]] std::string Formula::to_string() const {
    return getExpr()->to_string();
}

[[nodiscard]] std::ostream &operator<<(std::ostream &os, const Formula &formula) {
    os << formula.to_string();
    return os;
}

bool Formula::containsAtomic(const std::shared_ptr<Atomic> &atomic) const {
    auto atomics = Utils::getAtomics(this->getExpr());
    if (atomics.find(atomic->to_string()) != atomics.end()) {
        return true;
    }
    return false;
}

Formula Formula::deepCopy() const {
    return Formula(Formula::deepCopy(getExpr()));
}

bool operator==(const Formula &f1, const Formula &f2) {
    return *(f1.getExpr()) == *(f2.getExpr());
}

bool operator<(const Formula &f1, const Formula &f2) {
    return *(f1.getExpr()) < *(f2.getExpr());
}









