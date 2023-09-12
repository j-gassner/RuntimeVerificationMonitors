#pragma once

#include <stdexcept>
#include <memory>
#include "ExpressionTree/Expression.h"

/**
 * Interface for n-ary expressions.
 */
class NaryInterface : public Expression {
public:
    /**
     * Constructor.
     * @param symbol Symbol of n-ary expression.
     */
    explicit NaryInterface(const std::string &symbol)
            : Expression(symbol) {}

    /**
     * Create a given Nary or return the child if there is only one expresion.
     * @tparam Type Type of Nary
     * @param expressions
     * @return Nary if more than two elements in set, child otherwise.
     */
    template<class Type>
    static std::shared_ptr<Expression> makeNary(const typename Type::SetType_T &expressions) {
        auto nary = std::make_shared<Type>(expressions);
        if (nary->getExpressions().size() == 1) {
            return *(nary->getExpressions().begin());
        }
        else {
            return nary;
        }
    }

    /**
     * Number of expressions in expressions set.
     * @return Number of expressions.
     */
    virtual size_t size() = 0;

    /**
     * Checks whether expressions is empty.
     * @return True if empty, false otherwise.
     */
    virtual bool empty() = 0;

    using iterator = std::set<std::shared_ptr<Expression>>::iterator;

    /**
     * Adds an expression to the expressions set.
     * @param expr Expression to be added.
     */
    virtual void addExpression(std::shared_ptr<Expression> expr) = 0;

    /**
    * Searches expr in expressions and erases it if found.
    * @param expr Expression to be erased.
    * @return Iterator pointing to element after the erased one.
    */
    virtual iterator eraseExpression(std::shared_ptr<Expression> expr) = 0;

    /**
      * Erases an element from expressions at position of iter.
      * @param iter Iterator pointing to expression to be erased.
      * @return Iterator pointing to element after the erased one.
      */
    virtual iterator eraseExpression(iterator itr) = 0;

    /**
     * Searches for an expression in expressions set.
     * @param expr Expression to be found.
     * @return Iterator pointing to element if found or to end() if not found.
     */
    virtual iterator findExpression(std::shared_ptr<Expression> expr) = 0;

    /**
     * Checks whether an expression is in expressions set.
     * @param expr Expression to be found.
     * @return True if found, false otherwise.
     */
    virtual bool containsExpression(std::shared_ptr<Expression> expr) = 0;

    /**
     * Setter for expressions set.
     * @param begin Begin of new set.
     * @param end End of new set.
     */
    virtual void setExpressions(iterator begin, iterator end) = 0;

    /**
     * Begin() of expressions set.
     * @return Iterator to first element in expressions.
     */
    virtual iterator begin() = 0;

    /**
     * End() of expressions set.
     * @return Iterator to after last element in expressions.
     */
    virtual iterator end() = 0;

    static_assert(
            std::is_same_v<std::set<std::shared_ptr<Expression>>::iterator, std::multiset<std::shared_ptr<Expression>>::iterator>,
            "Iterator types of set and multiset differ!");

    /**
     * Comparison functor for shared pointers to expressions.
     * @note This should be used in child classes.
     */
    struct SharedPtrExprCompare {
        /**
         * Comparison by to_string.
         * @param left
         * @param right
         * @return
         */
        bool operator()(const std::shared_ptr<Expression> &left, const std::shared_ptr<Expression> &right) const {
            return left->to_string() < right->to_string();
        }
    };

//    /**
//    * Erases an element from expressions at position of iter, which is a set iterator.
//    * @param iter Iterator pointing to expression to be erased.
//    * @return Iterator pointing to element after the erased one.
//    */
//    [[nodiscard]] static std::shared_ptr<Expression> eraseExpression(std::shared_ptr<NaryInterface>& nary, const std::shared_ptr<Expression> &expr){
//        auto itr = nary->findExpression(expr);
//        return eraseExpression(nary, itr);
//    }


//    [[nodiscard]] static std::shared_ptr<Expression> eraseExpression(std::shared_ptr<NaryInterface>& nary, iterator itr){
//        if(itr != nary->end()){
//            nary->eraseExpression(itr);
//            if(nary->size() == 1){
//                return *(nary->begin());
//            }
//            if(nary->empty()){
//                throw std::runtime_error("Nary::eraseExpression() Removed last element in set.");
//            }
//        }
//        return nary;
//    }

};


