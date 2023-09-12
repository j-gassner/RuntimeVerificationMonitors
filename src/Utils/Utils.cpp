#include <set>
#include <algorithm>
#include <queue>
#include <iostream>

#include "Trace/Trace.h"
#include "Utils.h"
#include "Parser/Parser.h"
#include "ExpressionTree/Nary/Nary.h"
#include "ExpressionTree/Binary/Binary.h"
#include "ExpressionTree/Unary/Unary.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Unary/Bool/Not.h"
#include "ExpressionTree/Nary/Bool/And.h"
#include "ExpressionTree/Nary/Bool/Or.h"
#include "ExpressionTree/Nary/Bool/Xor.h"
#include "Timer.h"


bool
Utils::evaluateBooleanExpression(const std::shared_ptr<Expression> &expr, std::map<std::string, LazyBool> &eventMap) {
    // Atomic
    if (auto atomicExpr = std::dynamic_pointer_cast<Atomic>(expr)) {
        return eventMap.at(atomicExpr->to_string());
    }
    //Constant
    if (auto constantExpr = std::dynamic_pointer_cast<Constant>(expr)) {
        return constantExpr->getValue();
    }
    // Not
    if (auto notExpr = std::dynamic_pointer_cast<Not>(expr)) {
        return not evaluateBooleanExpression(notExpr->getLeft(), eventMap);
    }
    // And
    if (auto andExpr = std::dynamic_pointer_cast<And>(expr)) {
        auto res = true;
        for (auto &childExpr : *andExpr) {
            res and_eq evaluateBooleanExpression(childExpr, eventMap);
            // Short-circuit: if anything in the And is false the whole expression must be false.
            if(not res) {
                break;
            }
        }
        return res;
    }

    // Or
    if (auto orExpr = std::dynamic_pointer_cast<Or>(expr)) {
        auto res = false;
        for (auto &childExpr : *orExpr) {
            res or_eq evaluateBooleanExpression(childExpr, eventMap);
            // Short-circuit: if anything in the Or is true the whole expression must be true.
            if(res) {
                break;
            }
        }

        return res;
    }

    // Xor
    if (auto xorExpr = std::dynamic_pointer_cast<Xor>(expr)) {
        auto res = evaluateBooleanExpression(*xorExpr->begin(), eventMap);
        for (auto itr = ++xorExpr->begin(); itr != xorExpr->end(); ++itr) {
            res xor_eq evaluateBooleanExpression(*itr, eventMap);
        }

        return res;
    }
    return false;

}

Trace Utils::createTrace(const std::set<std::string> &atomics, std::vector<std::vector<std::string>> trueAtomics) {
    std::vector<Event> finalTrace;
    std::map<std::string, LazyBool> event;
    for (auto const &trueAtomic: trueAtomics) {
        for (auto const &atomic : atomics) {
            // Check if atomic exists in vector at current position
            bool atomicValue = trueAtomic.end() != std::find(trueAtomic.begin(), trueAtomic.end(), atomic);
            event[atomic] = LazyBool(atomicValue);
        }
        finalTrace.emplace_back(Event(event, &trueAtomic == &trueAtomics.back()));
        event.clear();
    }
    return Trace{finalTrace};
}

// Wrapper
std::set<std::string>
Utils::getAtomics(const Formula &formula) {
    return getAtomics(formula.getExpr(), {});
}

// Wrapper
std::set<std::string>
Utils::getAtomics(const std::shared_ptr<Expression> &expr) {
    return getAtomics(expr, {});
}

std::set<std::string>
Utils::getAtomics(const std::shared_ptr<Expression> &expr, std::set<std::string> atomics) {
    if (!expr) {
        return atomics;
    }

    // Nary
    if (auto nary = std::dynamic_pointer_cast<NaryInterface>(expr)) {
        for (const auto &itr : *nary) {
            atomics = getAtomics(itr, atomics);
        }
    }

        // Binary
    else if (auto binary = std::dynamic_pointer_cast<Binary>(expr)) {
        atomics = getAtomics(binary->getLeft(), atomics);
        atomics = getAtomics(binary->getRight(), atomics);
    }

        // Unary
    else if (auto unary = std::dynamic_pointer_cast<Unary>(expr)) {
        atomics = getAtomics(unary->getLeft(), atomics);
    }

        // Atomic
    else if (auto atomic = std::dynamic_pointer_cast<Atomic>(expr)) {
        atomics.emplace(expr->to_string());
    }

    // Don't count constants

    return atomics;

}

int Utils::getNumberOfAtomics(const std::shared_ptr<Expression> &expr) {
    return getAtomics(expr, {}).size();
}

Trace Utils::boolVectorToTrace(const std::set<std::string> &atomics, const std::vector<bool> &vector, bool terminal) {
    Event event = boolVectorToEvent(atomics, vector, terminal);
    return Trace{{event}};


}

// TODO terminal not needed (additional Event constructor)
Event Utils::boolVectorToEvent(const std::set<std::string> &atomics, const std::vector<bool> &vector, bool terminal) {
    std::map<std::string, LazyBool> eventMap;
    size_t i = 0;
    for (const auto &atomic : atomics) {
        eventMap.emplace(atomic, LazyBool(vector[i]));
        ++i;
    }
    return Event(eventMap, terminal);

}

Formula Utils::eventToFormula(Event &event) {
    std::map<std::string, LazyBool> eventMap = event.getEventMap();
    std::shared_ptr<Expression> firstExpr, secondExpr;

    And::SetType_T newSet;
    for (auto &[atomicName, atomicValue] : eventMap) {
        if (not atomicValue) {
            newSet.emplace(std::make_shared<Not>(std::make_shared<Atomic>(atomicName)));
        }
        else {
            newSet.emplace(std::make_shared<Atomic>(atomicName));
        }
    }
    return Formula(std::make_shared<And>(newSet));
}

std::vector<std::shared_ptr<Expression>>
Utils::subformulasBreadthFirstOrder(const Formula &formula) {
    std::queue<std::shared_ptr<Expression>> queue;
    std::vector<std::shared_ptr<Expression>> subformulas;
    if (!formula.getExpr()) {
        return subformulas;
    }
    queue.push(formula.getExpr());
    while (!queue.empty()) {
        auto currExpr = queue.front();
        queue.pop();
//        // Only add if not yet in subformulas
//        if (std::find_if(subformulas.begin(), subformulas.end(),
//                         [&](const std::shared_ptr<Expression> &expr) { return currExpr->to_string() == expr->to_string(); }) ==
//            subformulas.end()) {
        subformulas.push_back(currExpr);
        //}

        // Nary
        if (auto nary = std::dynamic_pointer_cast<NaryInterface>(currExpr)) {
            for (const auto &itr : *nary) {
                queue.push(itr);
            }
        }

            // Binary
        else if (auto binary = std::dynamic_pointer_cast<Binary>(currExpr)) {
            queue.push(binary->getLeft());
            queue.push(binary->getRight());
        }

            // Unary
        else if (auto unary = std::dynamic_pointer_cast<Unary>(currExpr)) {
            queue.push(unary->getLeft());
        }
    }
//    for (auto f:subformulas) {
//        std::cout << f->to_string() << std::endl;
//    }
    return subformulas;
}


std::vector<std::string> Utils::splitString(const std::string &stringOriginal, const std::string &delimiters) {
    std::vector<std::string> exprVector;

    std::size_t previous = 0, pos;
    while ((pos = stringOriginal.find_first_of(delimiters, previous)) != std::string::npos) {
        if (pos > previous) { exprVector.push_back(stringOriginal.substr(previous, pos - previous)); }
        previous = pos + 1;
    }
    if (previous < stringOriginal.length()) {
        exprVector.push_back(stringOriginal.substr(previous, std::string::npos));
    }

    return exprVector;
}

Trace Utils::createLazyTrace(const std::map<std::string, std::function<bool(int)>> &atomicsAndFunctions,
                             size_t length) {
    std::vector<Event> finalTrace;
    finalTrace.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        std::map<std::string, LazyBool> event;

        for (auto const &[atomic, valueFetcher] : atomicsAndFunctions) {
            auto valueFetcherBound = std::bind(valueFetcher, i);
            event[atomic] = LazyBool(valueFetcherBound);
        }
        finalTrace.emplace_back(Event(event, i == length - 1));
        event.clear();
    }
    return Trace{finalTrace};
}

