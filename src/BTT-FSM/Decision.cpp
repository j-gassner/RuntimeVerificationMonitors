#include "Decision.h"
#include "StateBTT_FSM.h"

#include <utility>
#include <sstream>

Decision::Decision(std::shared_ptr<Node> left, std::shared_ptr<Node> right,
                   std::shared_ptr<Expression> predicate) : left(std::move(left)), right(std::move(right)),
                                                            predicate(std::move(predicate)) {}

const std::shared_ptr<Node> &Decision::getLeft() const {
    return left;
}

void Decision::setLeft(const std::shared_ptr<Node> &left) {
    Decision::left = left;
}

const std::shared_ptr<Node> &Decision::getRight() const {
    return right;
}

void Decision::setRight(const std::shared_ptr<Node> &right) {
    Decision::right = right;
}

const std::shared_ptr<Expression> &Decision::getPredicate() const {
    return predicate;
}

void Decision::setPredicate(const std::shared_ptr<Expression> &predicate) {
    Decision::predicate = predicate;
}

std::string Decision::to_string() const {
    std::stringstream res;
    res << "(" << predicate->to_string() << " ? ";
    if (auto state = std::dynamic_pointer_cast<StateBTT_FSM>(left)) {
        if (not state->getId()) {
            res << "false : ";
        }
        else if (state->getId() == 1) {
            res << "true : ";
        }
        else {
            res << state->getId() << " : ";
        }
    }
    else {
        res << left->to_string() << " : ";
    }

    if (auto state = std::dynamic_pointer_cast<StateBTT_FSM>(right)) {
        if (not state->getId()) {
            res << "false";
        }
        else if (state->getId() == 1) {
            res << "true";
        }
        else {
            res << state->getId();
        }
    }
    else {
        res << right->to_string();
    }
    res << ")";
    return res.str();
}
