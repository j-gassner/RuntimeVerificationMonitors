#pragma once

#include "Formula/Formula.h"

/**
 * Applies rules to transform formula into conjunction of exclusive disjuntions.
 */
class RewriteVisitor : public ExpressionVisitor {
public:
    void rewrite(Formula &formula);

    //void visitExpression(Expression &expr, Event &event);

    [[nodiscard]] std::shared_ptr<Expression> visitAtomic(Atomic &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitConstant(Constant &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitAnd(And &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitOr(Or &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitXor(Xor &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitImplication(Implication &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitEquivalence(Equivalence &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitNot(Not &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitFuture(Future &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitGlobally(Globally &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitNextStrong(NextStrong &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitNextWeak(NextWeak &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitOnce(Once &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitPreviously(Previously &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitRelease(Release &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitUntil(Until &op, Event &event) override;

    [[nodiscard]] std::shared_ptr<Expression> visitEventOperator(EventOperator &op, Event &event) override;

};



