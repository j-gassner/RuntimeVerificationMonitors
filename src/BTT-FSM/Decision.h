#pragma once

#include <memory>
#include "ExpressionTree/Atomic/Atomic.h"
#include "Node.h"

/**
 * A Decision is a Node in a BTT with two outgoing branches.
 * Left leads to the next Node if the predicate is true; right to the next Node if predicate is false.
 */
class Decision : public Node {
private:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Expression> predicate;

public:
    /**
     * Constructor for a Decision.
     * @param left Next Node if predicate is true.
     * @param right Next Node if predicate is false.
     * @param predicate Predicate.
     */
    Decision(std::shared_ptr<Node> left, std::shared_ptr<Node> right,
             std::shared_ptr<Expression> predicate);

    /**
     * Getter for left.
     * @return Left.
     */
    [[nodiscard]] const std::shared_ptr<Node> &getLeft() const;

    /**
     * Getter for right.
     * @return Right.
     */

    [[nodiscard]] const std::shared_ptr<Node> &getRight() const;

    /**
     * Getter for predicate.
     * @return Predicate.
     */

    [[nodiscard]] const std::shared_ptr<Expression> &getPredicate() const;

    /**
     * Setter for left.
     * @param left
     */
    void setLeft(const std::shared_ptr<Node> &left);

    /**
     * Setter for right.
     * @param right
     */
    void setRight(const std::shared_ptr<Node> &right);

    /**
     * Setter for predicate.
     * @param predicate
     */
    void setPredicate(const std::shared_ptr<Expression> &predicate);

    /**
     * to_string() for Decision.
     * @return String representation of Decision.
     */
    [[nodiscard]] std::string to_string() const override;

};



