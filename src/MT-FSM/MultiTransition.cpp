#include "MultiTransition.h"
#include "Utils/Utils.h"

MultiTransition::MultiTransition(std::map<Formula, size_t> transitions) :
        transitions(std::move(
                transitions)) {}

std::map<Formula, size_t> &MultiTransition::getTransitions() {
    return transitions;
}

const std::map<Formula, size_t> &MultiTransition::getTransitions() const {
    return transitions;
}

std::string MultiTransition::to_string() const {
    std::stringstream ret;
    for (const auto &[formula, state] :transitions) {
        ret << formula.to_string() + " -> ";
        ret << state << std::endl;
    }
    return ret.str();
}

size_t MultiTransition::evaluate(std::map<std::string, LazyBool> &eventMap) const {
    for (const auto &[formula, state] :transitions) {
        if (Utils::evaluateBooleanExpression(formula.getExpr(), eventMap)) {
            return state;
        }
    }
    throw std::runtime_error("MultiTransition::evaluate() Event could not be mapped to any state.");
}
