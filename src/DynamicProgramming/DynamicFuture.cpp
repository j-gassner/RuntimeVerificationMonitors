#include <queue>
#include <algorithm>
#include <Utils/Utils.h>
#include <iostream>
#include "DynamicFuture.h"
#include "Dynamic.h"
#include "ExpressionTree/Unary/Temporal/LTLf/Future.h"
#include "ExpressionTree/Unary/Temporal/LTLf/NextStrong.h"
#include "ExpressionTree/Unary/Temporal/LTLf/NextWeak.h"
#include "ExpressionTree/Binary/Temporal/LTLf/Until.h"

std::vector<bool>
DynamicFuture::initializeNext(Event &event, const std::vector<std::shared_ptr<Expression>> &subformulas) {
    std::vector<bool> next;
    std::map<std::string, LazyBool> eventMap = event.getEventMap();
    next.resize(subformulas.size());
    // Fill next backwards
    for (size_t j = subformulas.size() - 1; j >= 0 && j < subformulas.size(); --j) {
        Dynamic::initialize(j, next, eventMap, subformulas);
        // Weak Next
        if (std::dynamic_pointer_cast<NextWeak>(subformulas[j])) {
            next[j] = true;
        }
            // Strong Next
        else if (std::dynamic_pointer_cast<NextStrong>(subformulas[j])) {
            next[j] = false;
        }
            // Future
        else if (std::dynamic_pointer_cast<Future>(subformulas[j])) {
            auto future = std::dynamic_pointer_cast<Future>(subformulas[j]);
            auto itr = std::find(subformulas.begin(), subformulas.end(), future->getLeft());
            auto indexLeft = std::distance(subformulas.begin(), itr);
            next[j] = next[indexLeft];
        }

            // Until
        else if (auto until = std::dynamic_pointer_cast<Until>(subformulas[j])) {
            auto itr = std::find(subformulas.begin(), subformulas.end(), until->getRight());
            auto indexRight = std::distance(subformulas.begin(), itr);
            next[j] = next[indexRight];
        }
    }

    return next;
}

std::vector<bool>
DynamicFuture::updateNow(Event &event, const std::vector<std::shared_ptr<Expression>> &subformulas,
                         const std::vector<bool> &next) {
    std::vector<bool> now;
    now.resize(next.size());
    std::map<std::string, LazyBool> eventMap = event.getEventMap();

    // j >= 0 && j < subformulas.size() to avoid underflow
    for (size_t j = subformulas.size() - 1; j >= 0 && j < subformulas.size(); --j) {
        Dynamic::update(j, now, next, eventMap, subformulas);
        // Next
        if (std::dynamic_pointer_cast<NextStrong>(subformulas[j]) ||
            std::dynamic_pointer_cast<NextWeak>(subformulas[j])) {
            auto unary = std::dynamic_pointer_cast<Unary>(subformulas[j]);
            auto itr = std::find(subformulas.begin(), subformulas.end(), unary->getLeft());
            auto indexLeft = std::distance(subformulas.begin(), itr);
            now[j] = next[indexLeft];
        }
            // Future
        else if (auto future = std::dynamic_pointer_cast<Future>(subformulas[j])) {
            auto itr = std::find(subformulas.begin(), subformulas.end(), future->getLeft());
            auto indexLeft = std::distance(subformulas.begin(), itr);
            now[j] = now[indexLeft] or next[j];
        }

            // Until
        else if (auto until = std::dynamic_pointer_cast<Until>(subformulas[j])) {
            auto itr = std::find(subformulas.begin(), subformulas.end(), until->getLeft());
            auto indexLeft = std::distance(subformulas.begin(), itr);
            itr = std::find(subformulas.begin(), subformulas.end(), until->getRight());
            auto indexRight = std::distance(subformulas.begin(), itr);
            now[j] = now[indexRight] or (now[indexLeft] and next[j]);
        }
    }
    return now;
}

bool DynamicFuture::checkTraceDynamically(const Formula &formula, Trace &trace) {
    // Empty trace
    if (trace.getTrace().empty()) {
        //std::cout << "Trace is empty" << std::endl;
        return false;
    }
    std::vector<std::shared_ptr<Expression>> subformulas = Utils::subformulasBreadthFirstOrder(formula);
    std::vector<bool> next = initializeNext(trace.getTraceRef()[trace.getLength() - 1], subformulas);
    if (!next[0]) {
        //std::cout << "Formula violated in last event " << trace.getLength() - 1 << std::endl;
        return false;
    }
    for (size_t i = trace.getLength() - 2; i >= 0 && i < trace.getLength() - 1; --i) {
        next = updateNow(trace.getTraceRef()[i], subformulas, next);
        // Only for safety properties!
        if (!next[0]) {
            //std::cout << "Formula violated in event " << i + 1 << std::endl;
            return false;
        }
    }
    return next[0];
}