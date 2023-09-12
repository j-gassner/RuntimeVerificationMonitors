#include <iostream>
#include "EventConsumingVisitor.h"
#include "ExpressionTree/Atomic/Atomic.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Unary/Bool/Not.h"
#include "ExpressionTree/Nary/Bool/And.h"
#include "ExpressionTree/Nary/Bool/Or.h"
#include "ExpressionTree/Nary/Bool/Xor.h"
#include "ExpressionTree/Binary/Bool/Implication.h"
#include "ExpressionTree/Binary/Bool/Equivalence.h"
#include "ExpressionTree/Unary/EventOperator.h"
#include "ExpressionTree/Unary/Temporal/LTLf/Globally.h"
#include "ExpressionTree/Unary/Temporal/LTLf/Future.h"
#include "ExpressionTree/Unary/Temporal/LTLf/NextStrong.h"
#include "ExpressionTree/Unary/Temporal/LTLf/NextWeak.h"
#include "ExpressionTree/Unary/Temporal/PLTLf/Once.h"
#include "ExpressionTree/Unary/Temporal/PLTLf/Previously.h"
#include "ExpressionTree/Binary/Temporal/LTLf/Release.h"
#include "ExpressionTree/Binary/Temporal/LTLf/Until.h"
#include "Trace/Event.h"

void EventConsumingVisitor::consumeEvent(Formula &formula, Event &event) {
    std::shared_ptr<EventOperator> eventOperator =
            std::make_shared<EventOperator>(formula.getExpr(), event);
    formula.setExpr(eventOperator->accept(*this, event));
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitAtomic(Atomic &op, Event &event) {
    return std::make_shared<Atomic>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitConstant(Constant &op, Event &event) {
    return std::make_shared<Constant>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitAnd(And &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<And>(op);
}

std::shared_ptr<Expression> EventConsumingVisitor::visitOr(Or &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Or>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitXor(Xor &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Xor>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitImplication(Implication &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Implication>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitEquivalence(Equivalence &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Equivalence>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitNot(Not &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Not>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitFuture(Future &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Future>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitGlobally(Globally &op, Event &event) {
    visitExpression(op, event);
    visitExpression(op, event);
    return std::make_shared<Globally>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitNextStrong(NextStrong &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<NextStrong>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitNextWeak(NextWeak &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<NextWeak>(op);
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitOnce(Once &op, Event &event) {
    visitExpression(op, event);
    auto ret = std::make_shared<Once>(op);
    visitExpression(op, event);
    return ret;
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitPreviously(Previously &op, Event &event) {
    visitExpression(op, event);
    auto ret = std::make_shared<Previously>(op);
    visitExpression(op, event);
    return ret;
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitRelease(Release &op, Event &event) {
    visitExpression(op, event);
    auto ret = std::make_shared<Release>(op);
    visitExpression(op, event);
    return ret;
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitUntil(Until &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<Until>(op.getLeft(), op.getRight());
}

std::shared_ptr<Expression>
EventConsumingVisitor::visitEventOperator(EventOperator &op,
                                          Event &event) {

    std::shared_ptr<Expression> ret;

    // Apply eventMap to atomic
    if (auto atomic = std::dynamic_pointer_cast<Atomic>(op.getLeft())) {
        ret = std::make_shared<Constant>(event.getValue(*atomic));
    }
    else if (auto constant = std::dynamic_pointer_cast<Constant>(op.getLeft())) {
        ret = std::make_shared<Constant>(constant->getValue());
    }
        // And
    else if (auto andExpr = std::dynamic_pointer_cast<And>(op.getLeft())) {
        And::SetType_T newExprSet;
        for (const auto &itr : *andExpr) {
            auto eventConsumingExpr = std::make_shared<EventOperator>(itr, event);
            newExprSet.emplace(eventConsumingExpr);
        }
        ret = std::make_shared<And>(newExprSet);
    }

        // Or
    else if (auto orExpr = std::dynamic_pointer_cast<Or>(op.getLeft())) {
        Or::SetType_T newExprSet;
        for (const auto &itr : *orExpr) {
            auto eventConsumingExpr = std::make_shared<EventOperator>(itr, event);
            newExprSet.emplace(eventConsumingExpr);
        }
        ret = std::make_shared<Or>(newExprSet);
    }
        // Xor
    else if (auto xorExpr = std::dynamic_pointer_cast<Xor>(op.getLeft())) {
        Xor::SetType_T newExprSet;
        for (const auto &itr : *xorExpr) {
            auto eventConsumingExpr = std::make_shared<EventOperator>(itr, event);
            newExprSet.emplace(eventConsumingExpr);
        }
        ret = std::make_shared<Xor>(newExprSet);

    }
        // Globally
    else if (auto globally = std::dynamic_pointer_cast<Globally>(op.getLeft())) {
        if (!event.isTerminal()) {
            And::SetType_T newSet;
            auto eventOperatorExpr = std::make_shared<EventOperator>(globally->getLeft(), event);
            newSet.emplace(eventOperatorExpr);
            newSet.emplace(globally);
            ret = std::make_shared<And>(newSet);
        }
        else {
            ret = std::make_shared<EventOperator>(globally->getLeft(), event);
        }
    }
        // Weak Next
    else if (auto nextWeak = std::dynamic_pointer_cast<NextWeak>(op.getLeft())) {
        if (!event.isTerminal()) {
            ret = nextWeak->getLeft();
        }
        else {
            ret = std::make_shared<Constant>(true);
        }
    }
        // Strong Next
    else if (auto nextStrong = std::dynamic_pointer_cast<NextStrong>(op.getLeft())) {
        if (!event.isTerminal()) {
            ret = nextStrong->getLeft();
        }
        else {
            ret = std::make_shared<Constant>(false);
            //ret = std::make_shared<EventOperator>(nextStrong->getLeft(), event);
        }
    }
        // Future
    else if (auto future = std::dynamic_pointer_cast<Future>(op.getLeft())) {
        if (!event.isTerminal()) {
            Or::SetType_T newSet;
            auto eventOperatorExpr = std::make_shared<EventOperator>(future->getLeft(), event);
            newSet.emplace(eventOperatorExpr);
            newSet.emplace(future);
            ret = std::make_shared<Or>(newSet);
        }
        else {
            ret = std::make_shared<EventOperator>(future->getLeft(), event);
        }
    }
        // Until
    else if (auto until = std::dynamic_pointer_cast<Until>(op.getLeft())) {
        if (!event.isTerminal()) {
            Or::SetType_T newSetOr;
            And::SetType_T newSetAnd;
            auto orElement = std::make_shared<EventOperator>(until->getRight(), event);
            auto andElement = std::make_shared<EventOperator>(until->getLeft(), event);
            newSetOr.emplace(orElement);
            newSetAnd.emplace(andElement);
            newSetAnd.emplace(until);
            auto newAnd = std::make_shared<And>(newSetAnd);
            newSetOr.emplace(newAnd);
            ret = std::make_shared<Or>(newSetOr);
        }
        else {
            ret = std::make_shared<EventOperator>(until->getRight(), event);
        }
    }
        // Previously
    else if (auto previously = std::dynamic_pointer_cast<Previously>(op.getLeft())) {
        if (!event.isTerminal()) {
            ret = previously->getLeft();
        }
        else {
            ret = std::make_shared<Constant>(true);
        }
    }
        // Once
    else if (auto once = std::dynamic_pointer_cast<Once>(op.getLeft())) {
        if (!event.isTerminal()) {
            Or::SetType_T newSet;
            auto eventOperatorExpr = std::make_shared<EventOperator>(once->getLeft(), event);
            newSet.emplace(eventOperatorExpr);
            newSet.emplace(once);
            ret = std::make_shared<Or>(newSet);
        }
        else {
            ret = std::make_shared<EventOperator>(once->getLeft(), event);
        }
    }
    return ret->accept(*this, event);
}
