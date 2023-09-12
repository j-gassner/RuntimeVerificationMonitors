#pragma once

#include <utility>
#include <algorithm>
#include <sstream>

#include "ExpressionTree/Nary/NaryInterface.h"

/**
 * Class representing all associative expressions (And, Or, Xor).
 * @tparam SetType Type of the set used respective expression.
 * @tparam Actual Actual type of expression.
 */
template<class SetType, class Actual>
class Nary : public NaryInterface {
protected:
    SetType expressions;

public:
    /**
     * Type alias of the internally used set.
     */
    using SetType_T = SetType;

    /**
     * Constructor.
     * @param symbol Symbol of the respective expression.
     * @param expressions Set of expressions connected by this expression.
     */
    explicit Nary(const std::string &symbol, const SetType &expressions)
            : NaryInterface(symbol) {
        Nary<SetType, Actual>::setExpressions(expressions.begin(), expressions.end());
    }

    /**
     * Getter for expressions set.
     * @return Set of expressions.
     */
    [[nodiscard]] const SetType &getExpressions() const {
        return expressions;
    }

    /**
     * Iterator to beginning of a set.
     * @return Iterator to beginning of set.
     */
    [[nodiscard]] std::set<std::shared_ptr<Expression>>::iterator begin() override {
        return expressions.begin();
    }

    /**
     * Iterator to end of a set.
     * @return Iterator to end of set.
     */
    [[nodiscard]] std::set<std::shared_ptr<Expression>>::iterator end() override {
        return expressions.end();
    }

    /**
     * Adds an expresion to a set.
     * @param expr
     */
    void addExpression(std::shared_ptr<Expression> expr) override {
        // If we want to add an expression of the same type pull it into expressions
        // (a & b & (c & d)) -> (a & b & c & d)
        if (auto nary = std::dynamic_pointer_cast<Actual>(expr)) {
            for (auto &itr : *nary) {
                addExpression(itr);
            }
        }
        else {
            expressions.emplace(expr);
        }
    }

    /**
     * Erases an expression at position iter from a set.
     * @param iter
     * @return True if expression was erased, false otherwise.
     */
    [[nodiscard]] std::set<std::shared_ptr<Expression>>::iterator
    erase(std::set<std::shared_ptr<Expression>>::iterator iter) {
        return expressions.erase(iter);
    }

    /**
    * Erases an element from expressions at position of iter, which is a set iterator.
    * @param iter Iterator pointing to expression to be erased.
    * @return Iterator pointing to element after the erased one.
    */
    iterator eraseExpression(std::shared_ptr<Expression> expr) override {
        auto itr = findExpression(expr);
        return eraseExpression(itr);
    }

    /**
     * Erase an expression from a set.
     * @param itr
     * @return Iterator to erased position.
     */
    iterator eraseExpression(iterator itr) override {
        if (itr != expressions.end()) {
            return expressions.erase(itr);
        }
        return expressions.end();
    }

    /**
     * Finds an expression and returns an iterator to it.
     * @param expr
     * @return Iterator to searched expression.
     */
    iterator findExpression(std::shared_ptr<Expression> expr) override {
        return expressions.find(expr);
    }

    /**
     * Check if expression exists in a set.
     * @param expr
     * @return True if contained, false otherwise.
     */
    bool containsExpression(std::shared_ptr<Expression> expr) override {
        return findExpression(expr) != expressions.end();
    }

    /**
     * Setter for expressions.
     * @param begin
     * @param end
     */
    void setExpressions(NaryInterface::iterator begin, NaryInterface::iterator end) override {
        expressions.clear();
        for (auto itr = begin; itr != end; ++itr) {
            addExpression(*itr);
        }
    }

    /**
     * Size of an expressions set.
     * @return size of expressions.
     */
    [[nodiscard]] size_t size() override {
        return expressions.size();
    }

    /**
     * Checks if set is empty.
     * @return True if empty, false otherwise.
     */
    [[nodiscard]] bool empty() override {
        return expressions.size() == 0;
    }

    /**
     * To_string().
     * @return String representation of the contained set.
     */
    [[nodiscard]] std::string to_string() const override {
        std::stringstream ret;
        ret << "(";
        for (auto itr = getExpressions().cbegin(); itr != --getExpressions().cend(); ++itr) {
            ret << (*itr)->to_string() << " " << getSymbol() << " ";
        }
        ret << (*--getExpressions().cend())->to_string() << ")";
        return ret.str();
    }

};




