#include <iostream>
#include "BasicRewriteVisitor.h"
#include "Trace/Event.h"
#include "RewriteVisitor.h"
#include "ExpressionTree/Unary/EventOperator.h"
#include "ExpressionTree/Atomic/Atomic.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Unary/Bool/Not.h"
#include "ExpressionTree/Nary/Bool/And.h"
#include "ExpressionTree/Nary/Bool/Or.h"
#include "ExpressionTree/Nary/Bool/Xor.h"
#include "ExpressionTree/Binary/Bool/Equivalence.h"
#include "ExpressionTree/Binary/Bool/Implication.h"
#include "ExpressionTree/Unary/Temporal/LTLf/Globally.h"
#include "ExpressionTree/Unary/Temporal/LTLf/Future.h"
#include "ExpressionTree/Unary/Temporal/LTLf/NextStrong.h"
#include "ExpressionTree/Unary/Temporal/LTLf/NextWeak.h"
#include "ExpressionTree/Unary/Temporal/PLTLf/Once.h"
#include "ExpressionTree/Unary/Temporal/PLTLf/Previously.h"
#include "ExpressionTree/Binary/Temporal/LTLf/Release.h"
#include "ExpressionTree/Binary/Temporal/LTLf/Until.h"
#include "RewriteVisitorUtils.h"

void BasicRewriteVisitor::rewrite(Formula &formula) {
    std::map<std::string, LazyBool> map;
    // Dummy eventMap
    Event event(map, false);

    auto before = Formula::deepCopy(formula.getExpr());
    formula.setExpr(formula.getExpr()->accept(*this, event));
    while (before->to_string() != formula.getExpr()->to_string()) {
        before = Formula::deepCopy(formula.getExpr());
        formula.setExpr(formula.getExpr()->accept(*this, event));
    }
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitAtomic(Atomic &op, Event &event) {
    return std::make_shared<Atomic>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitConstant(Constant &op, Event &event) {
    return std::make_shared<Constant>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitAnd(And &op, Event &event) {
    visitExpression(op, event);

    // I'm a copy!
    auto expressions = op.getExpressions();

    // Check for false
    if (expressions.find(std::make_shared<Constant>(false)) != expressions.end()) {
        return std::make_shared<Constant>(false);
    }
    // Remove true
    auto ret = expressions.equal_range(std::make_shared<Constant>(true));
    expressions.erase(ret.first, ret.second);

    // If everything was removed there has only been a true -> return true
    if (expressions.empty()) {
        return std::make_shared<Constant>(true);
    }
    // Only one element left
    if (expressions.size() == 1) {
        return *expressions.begin();
    }


    // Absorption a & (a | b) = a
    RewriteVisitorUtils::absorption<Or>(expressions);

    // Only one element left
    if (expressions.size() == 1) {
        return *expressions.begin();
    }

    // !a & a = false
    RewriteVisitorUtils::reduceNegations<false>(expressions);

    // Only one element left
    if (expressions.size() == 1) {
        return *expressions.begin();
    }

    return std::make_shared<And>(expressions);

}

std::shared_ptr<Expression> BasicRewriteVisitor::visitOr(Or &op, Event &event) {
    visitExpression(op, event);
    auto expressions = op.getExpressions();

    // Check for true
    if (expressions.find(std::make_shared<Constant>(true)) != expressions.end()) {
        return std::make_shared<Constant>(true);
    }
    // Remove false
    auto ret = expressions.equal_range(std::make_shared<Constant>(false));
    expressions.erase(ret.first, ret.second);

    // If everything was removed there has only been a false -> return false
    if (expressions.empty()) {
        return std::make_shared<Constant>(false);
    }

    // Only one element left
    if (expressions.size() == 1) {
        return *expressions.begin();
    }

    // Absorption a | (a & b) = a
    RewriteVisitorUtils::absorption<And>(expressions);

    // Only one element left
    if (expressions.size() == 1) {
        return *expressions.begin();
    }

    // !a | a = true
    RewriteVisitorUtils::reduceNegations<true>(expressions);

    // Only one element left
    if (expressions.size() == 1) {
        return *expressions.begin();
    }

    return std::make_shared<Or>(expressions);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitXor(Xor &op, Event &event) {
    visitExpression(op, event);

    auto expressions = op.getExpressions();
    Xor::SetType_T newXorSet;

    // !a ^ a = true
    RewriteVisitorUtils::reduceNegations<true>(expressions);

    // Remove unnecessary duplicates
    for (auto itr = expressions.begin(); itr != expressions.end();) {
        // a ^ a = false
        if (expressions.count(*itr) % 2 == 0) {
            newXorSet.emplace(std::make_shared<Constant>(false));
        }
            // a ^ a ^ a = a
        else {
            newXorSet.emplace(*itr);
        }
        // Erase duplicates so we don't have to look at them again in the loop
        auto ret = expressions.equal_range(*itr);
        itr = expressions.erase(ret.first, ret.second);
    }

    // a ^ false = a -> remove false
    // Number of false does not matter
    auto ret = newXorSet.equal_range(std::make_shared<Constant>(false));
    newXorSet.erase(ret.first, ret.second);

    // Only false was left
    if (newXorSet.empty()) {
        return std::make_shared<Constant>(false);
    }
    // Only one element left
    if (newXorSet.size() == 1) {
        return *newXorSet.begin();
    }
    return std::make_shared<Xor>(newXorSet);

}

std::shared_ptr<Expression> BasicRewriteVisitor::visitImplication(Implication &op, Event &event) {
    visitExpression(op, event);
    // a -> a = true
    if (*op.getLeft() == *op.getRight()) {
        return std::make_shared<Constant>(true);
    }
    // true -> false = false
    if (op.getLeft()->isConstTrue() && op.getRight()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }
    // a -> true = true
    if (op.getRight()->isConstTrue()) {
        return std::make_shared<Constant>(true);
    }
    // false -> a = true
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(true);
    }

    // a -> b = !a | b
    Or::SetType_T orSet{std::make_shared<Not>(op.getLeft()), op.getRight()};
    return std::make_shared<Or>(orSet);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitNot(Not &op, Event &event) {
    visitExpression(op, event);
    // !true = false
    if (op.getLeft()->isConstTrue()) {
        return std::make_shared<Constant>(false);
    }
    // !false = true
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(true);
    }
    return std::make_shared<Not>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitFuture(Future &op, Event &event) {
    visitExpression(op, event);
    // F(false) = false
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }
    // Idempotence
    if (auto future = std::dynamic_pointer_cast<Future>(op.getLeft())) {
        return future;
    }

    // Absorption F(G(F(a))) = G(F(a))
    if (auto globally = std::dynamic_pointer_cast<Globally>(op.getLeft())) {
        if (std::dynamic_pointer_cast<Future>(globally->getLeft())) {
            return globally;
        }
    }
    return std::make_shared<Future>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitGlobally(Globally &op, Event &event) {
    visitExpression(op, event);
    // G(false) = false
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }
    // G(true) = true
    if (op.getLeft()->isConstTrue()) {
        return std::make_shared<Constant>(true);
    }
    // Idempotence
    if (auto globally = std::dynamic_pointer_cast<Globally>(op.getLeft())) {
        return globally;
    }

    // Absorption G(F(G(a))) = F(G(a))
    if (auto future = std::dynamic_pointer_cast<Future>(op.getLeft())) {
        if (std::dynamic_pointer_cast<Globally>(future->getLeft())) {
            return future;
        }
    }
    return std::make_shared<Globally>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitNextStrong(NextStrong &op, Event &event) {
    visitExpression(op, event);
    // X(false) = false
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }
    return std::make_shared<NextStrong>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitNextWeak(NextWeak &op, Event &event) {
    visitExpression(op, event);
    return std::make_shared<NextWeak>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitOnce(Once &op, Event &event) {
    visitExpression(op, event);
    // O(false) = false
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }

    // Idempotence
    if (auto once = std::dynamic_pointer_cast<Once>(op.getLeft())) {
        return once;
    }
    return std::make_shared<Once>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitPreviously(Previously &op, Event &event) {
    visitExpression(op, event);
    // P(false) = false
    if (op.getLeft()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }
    return std::make_shared<Previously>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitRelease(Release &op, Event &event) {
    visitExpression(op, event);
    // a R true = true
    if (op.getRight()->isConstTrue()) {
        return std::make_shared<Constant>(true);
    }
    // a R false = false
    if (op.getRight()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }

    // Idempotence
    if (auto release = std::dynamic_pointer_cast<Release>(op.getLeft())) {
        if (release->getRight() == op.getRight()) {
            return release;
        }
    }
    if (auto release = std::dynamic_pointer_cast<Release>(op.getRight())) {
        if (release->getLeft() == op.getLeft()) {
            return release;
        }
    }
    return std::make_shared<Release>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitUntil(Until &op, Event &event) {
    visitExpression(op, event);
    // a U false = false
    if (op.getRight()->isConstFalse()) {
        return std::make_shared<Constant>(false);
    }

    // Idempotence
    if (auto until = std::dynamic_pointer_cast<Until>(op.getLeft())) {
        if (until->getRight() == op.getRight()) {
            return until;
        }
    }
    if (auto until = std::dynamic_pointer_cast<Until>(op.getRight())) {
        if (until->getLeft() == op.getLeft()) {
            return until;
        }
    }
    return std::make_shared<Until>(op);

}

std::shared_ptr<Expression> BasicRewriteVisitor::visitEventOperator(EventOperator &op, Event &event) {
    return std::make_shared<EventOperator>(op);
}

std::shared_ptr<Expression> BasicRewriteVisitor::visitEquivalence(Equivalence &op, Event &event) {
    // TODO check if same/different formula left and right
    if (op.getLeft() == op.getRight()) {
        return std::make_shared<Constant>(true);
    }
    //a -> b & b -> a
    auto newLeft = std::make_shared<Implication>(op.getLeft(), op.getRight());
    auto newRight = std::make_shared<Implication>(op.getRight(), op.getLeft());
    And::SetType_T andSet{newLeft, newRight};
    return std::make_shared<And>(andSet);
}

