#pragma once

#include <string>
#include <memory>
#include <set>
#include <utility>

#include "Symbols/Symbols.h"
#include "Rewriting/ExpressionVisitor.h"

class Event;

/**
 * Parent class for all expressions.
 */
class Expression {
private:
    std::string symbol;

public:
    /**
     * Constructor.
     * @param symbol Symbol of the expression.
     */
    explicit Expression(std::string symbol)
            : symbol(std::move(symbol)) {
    }

    /**
     * Default constructor.
     * @param expression Expression.
     */
    Expression(const Expression &expression) = default;

    /**
     * Setter for symbol.
     * @param symb Symbol.
     */
    void setSymbol(const std::string &symb);

    /**
     * Getter for symbol.
     * @return Symbol.
     */
    [[nodiscard]] const std::string &getSymbol() const;

    /**
     * to_string() for an expression.
     * @return String representation of an expression.
     */
    [[nodiscard]] virtual std::string to_string() const;

    /**
    * Clones this expression.
    * @return New shared_ptr of this expression.
    */
    virtual std::shared_ptr<Expression> clone() = 0;

    /**
     * Accept function for visitor pattern.
     * @param visitor Visitor.
     * @param event Event.
     * @return Result of visit function of respective expression.
     */
    virtual std::shared_ptr<Expression> accept(ExpressionVisitor &, Event &) = 0;

    /**
     * Checks if expression is a specific Constant.
     * @param constant True or false.
     * @return True if value matches, false otherwise.
     */
    [[nodiscard]] bool isConst(bool constant) const;

    /**
     * Checks if expression is a Constant with value true.
     * @return True if value is true, false otherwise.
     */
    [[nodiscard]] bool isConstTrue() const;

    /**
     * Checks if expression is a Constant with value false.
     * @return True if value is false, false otherwise.
     */
    [[nodiscard]] bool isConstFalse() const;


};

bool operator==(const Expression &e1, const Expression &e2);

bool operator<(const Expression &e1, const Expression &e2);




