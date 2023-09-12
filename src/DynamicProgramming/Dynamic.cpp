#include <Utils/LazyBool.h>
#include "Dynamic.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Atomic/Atomic.h"
#include "ExpressionTree/Unary/Bool/Not.h"
#include "ExpressionTree/Nary/Bool/And.h"
#include "ExpressionTree/Nary/Bool/Or.h"
#include "ExpressionTree/Nary/Bool/Xor.h"
#include "ExpressionTree/Binary/Bool/Implication.h"
#include "ExpressionTree/Unary/Temporal/LTLf/Globally.h"
#include "ExpressionTree/Unary/Temporal/PLTLf/Once.h"
#include "ExpressionTree/Unary/Temporal/PLTLf/Previously.h"
#include "DynamicFuture.h"
#include "DynamicPast.h"

void
Dynamic::initialize(size_t j, std::vector<bool> &initVector, std::map<std::string, LazyBool> &eventMap,
                    const std::vector<std::shared_ptr<Expression>> &subformulas) {
    // TODO evaluate predicates
    // Atomic
    if (auto atomic = std::dynamic_pointer_cast<Atomic>(subformulas[j])) {
        initVector[j] = eventMap.at(atomic->to_string());
    }
    // Constant
    if (auto constant = std::dynamic_pointer_cast<Constant>(subformulas[j])) {
        initVector[j] = constant->getValue();
    }
        // Not
    else if (auto notExpr = std::dynamic_pointer_cast<Not>(subformulas[j])) {
        auto itr = std::find(subformulas.begin(), subformulas.end(), notExpr->getLeft());
        auto indexLeft = std::distance(subformulas.begin(), itr);
        initVector[j] = not initVector[indexLeft];
    }

        // And
    else if (std::dynamic_pointer_cast<And>(subformulas[j])) {
        initVector[j] = applyBooleanOperation(j, subformulas, initVector,
                                              [&](const auto &left, const auto &right) { return left and right; });
    }
        // Or
    else if (std::dynamic_pointer_cast<Or>(subformulas[j])) {
        initVector[j] = applyBooleanOperation(j, subformulas, initVector,
                                              [&](const auto &left, const auto &right) { return left or right; });
    }

        // Xor
    else if (std::dynamic_pointer_cast<Xor>(subformulas[j])) {
        initVector[j] = applyBooleanOperation(j, subformulas, initVector,
                                              [&](const auto &left, const auto &right) { return left xor right; });
    }

        // Implication
    else if (std::dynamic_pointer_cast<Implication>(subformulas[j])) {
        initVector[j] = applyBooleanOperation(j, subformulas, initVector,
                                              [&](const auto &left, const auto &right) { return not left or right; });
    }

        // Globally
    else if (auto globally = std::dynamic_pointer_cast<Globally>(subformulas[j])) {
        auto itr = std::find(subformulas.begin(), subformulas.end(), globally->getLeft());
        auto indexLeft = std::distance(subformulas.begin(), itr);
        initVector[j] = initVector[indexLeft];
    }

}

void
Dynamic::update(size_t j, std::vector<bool> &updateVector, std::vector<bool> oldVector,
                std::map<std::string, LazyBool> &eventMap,
                const std::vector<std::shared_ptr<Expression>> &subformulas) {
    // Atomic
    if (auto atomic = std::dynamic_pointer_cast<Atomic>(subformulas[j])) {
        updateVector[j] = eventMap.at(atomic->to_string());
    }
    // Constant
    if (auto constant = std::dynamic_pointer_cast<Constant>(subformulas[j])) {
        updateVector[j] = constant->getValue();
    }
        // Not
    else if (auto notExpr = std::dynamic_pointer_cast<Not>(subformulas[j])) {
        auto itr = std::find(subformulas.begin(), subformulas.end(), notExpr->getLeft());
        auto indexLeft = std::distance(subformulas.begin(), itr);
        updateVector[j] = not updateVector[indexLeft];
    }

        // And
    else if (std::dynamic_pointer_cast<And>(subformulas[j])) {
        updateVector[j] = applyBooleanOperation(j, subformulas, updateVector,
                                                [&](const auto &left, const auto &right) { return left and right; });
    }
        // Or
    else if (std::dynamic_pointer_cast<Or>(subformulas[j])) {
        updateVector[j] = applyBooleanOperation(j, subformulas, updateVector,
                                                [&](const auto &left, const auto &right) { return left or right; });
    }

        // Xor
    else if (std::dynamic_pointer_cast<Xor>(subformulas[j])) {
        updateVector[j] = applyBooleanOperation(j, subformulas, updateVector,
                                                [&](const auto &left, const auto &right) { return left xor right; });
    }

        // Implication
    else if (std::dynamic_pointer_cast<Implication>(subformulas[j])) {
        updateVector[j] = applyBooleanOperation(j, subformulas, updateVector,
                                                [&](const auto &left, const auto &right) { return not left or right; });
    }

        // Globally
    else if (auto globally = std::dynamic_pointer_cast<Globally>(subformulas[j])) {
        auto itr = std::find(subformulas.begin(), subformulas.end(), globally->getLeft());
        auto indexLeft = std::distance(subformulas.begin(), itr);
        updateVector[j] = updateVector[indexLeft] and oldVector[j];
    }
}

bool Dynamic::dynamic(const Formula& formula, Trace& trace, bool past) {
    if(!past){
        return DynamicFuture::checkTraceDynamically(formula, trace);
    }
    return DynamicPast::checkTraceDynamically(formula, trace);
}
