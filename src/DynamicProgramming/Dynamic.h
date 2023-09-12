#pragma once

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Formula/Formula.h"
#include "Trace/Trace.h"
#include "ExpressionTree/Nary/NaryInterface.h"
#include "ExpressionTree/Expression.h"
#include "ExpressionTree/Binary/Bool/Implication.h"

/**
 * Dynamic Encapsulates functions needed by both DynamicFuture and DynamicPast for dynamic programming approach.
 */
namespace Dynamic {

    /**
     * Initializes vector pre/next with values according to eventMap.
     * @param j Index of subformula in initVector.
     * @param initVector Vector where initial values are written to.
     * @param eventMap Map of events with truth values of all predicates.
     * @param subformulas Vector of all subformulas of the formula to be verified.
     */
    void
    initialize(size_t j, std::vector<bool> &initVector, std::map<std::string, LazyBool> &eventMap,
               const std::vector<std::shared_ptr<Expression>> &subformulas);

    /**
     * Updates newVector according to the values in oldVector.
     * @param j Index of subformula vectors.
     * @param updateVector Subformula values of current event.
     * @param oldVector Subformula values of previous event.
     * @param eventMap Map of events with truth values of all predicates.
     * @param subformulas Vector of all subformulas of the formula to be verified.
     */
    void
    update(size_t j, std::vector<bool> &updateVector, std::vector<bool> oldVector,
           std::map<std::string, LazyBool> &eventMap,
           const std::vector<std::shared_ptr<Expression>> &subformulas);

    bool dynamic(const Formula& formula, Trace& trace, bool past);

    /**
     * Computes truth value of an expression of type Implication or Nary.
     * @tparam F Expects two bool and return one bool.
     * @param j Current index in vector that is evaluated.
     * @param subformulas Vector of all subformulas of the formula to be verified.
     * @param values Evaluation vector.
     * @param function Function for fold.
     * @return Value of expression at index j in values vector.
     */
    template<class F>
    [[nodiscard]] bool applyBooleanOperation(size_t j, const std::vector<std::shared_ptr<Expression>> &subformulas,
                                             const std::vector<bool> &values, F function) {
        // Implication
        if (auto impl = std::dynamic_pointer_cast<Implication>(subformulas[j])) {
            auto itr = std::find(subformulas.begin(), subformulas.end(), impl->getLeft());
            auto indexLeft = std::distance(subformulas.begin(), itr);
            itr = std::find(subformulas.begin(), subformulas.end(), impl->getRight());
            auto indexRight = std::distance(subformulas.begin(), itr);
            return function(values[indexLeft], values[indexRight]);
        }

        // And/Or/Xor
        // Iterate over set and apply function
        if (auto nary = std::dynamic_pointer_cast<NaryInterface>(subformulas[j])) {
            bool res;
            for (auto exprItr = nary->begin(); exprItr != nary->end(); ++exprItr) {
                auto itr = std::find(subformulas.begin(), subformulas.end(), *exprItr);
                auto index = std::distance(subformulas.begin(), itr);
                if (exprItr == nary->begin()) {
                    res = values[index];
                }
                else {
                    res = function(res, values[index]);
                }
            }
            return res;
        }

        throw std::runtime_error("Dynamic::applyBooleanOperation() subformulas[j] has to be Nary or Implication.");
    }
}




