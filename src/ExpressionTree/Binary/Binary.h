#pragma once

#include "ExpressionTree/Expression.h"

/**
 * Parent class for all binary expressions.
 */
class Binary : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    /**
     * Constructor.
     * @param symbol Symbol of the respective expression.
     * @param left Left expression.
     * @param right Right expression.
     */
    Binary(std::string symbol, std::shared_ptr<Expression> left,
           std::shared_ptr<Expression> right)
            : Expression(std::move(symbol)), left(std::move(left)), right(std::move(right)) {
    }

    /**
     * Getter for left expression.
     * @return Left expression.
     */
    [[nodiscard]] const std::shared_ptr<Expression> &getLeft() const;

    /**
     * Getter for right expression.
     * @return Right expression.
     */
    [[nodiscard]] const std::shared_ptr<Expression> &getRight() const;

    /**
     * Setter for left expression.
     * @param left New left expression.
     */
    void setLeft(const std::shared_ptr<Expression> &left);

    /**
     * Setter for right expression.
     * @param left New right expression.
     */
    void setRight(const std::shared_ptr<Expression> &rightExpr);

    [[nodiscard]] std::string to_string() const override;
};




