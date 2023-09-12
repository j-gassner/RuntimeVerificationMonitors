#pragma once

#include <memory>
#include <algorithm>
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Unary/Bool/Not.h"

namespace RewriteVisitorUtils {

    /**
     * Encapsulates a double for loop over expressions.
     *
     * @tparam SetType Type of expression set.
     * @tparam F Function type.
     * @param expressions
     * @param f Function for pair of iterators. Should return true if erase was called with outer iterator.
     */
    template<class SetType, class F>
    void doubleLoop(SetType &expressions, F f) {
        for (auto outerIter = expressions.begin(); outerIter != expressions.end();) {
            bool erased = false;
            for (auto innerIter = expressions.begin();
                 innerIter != outerIter && innerIter != expressions.end(); ++innerIter) {
                if (f(outerIter, innerIter)) {
                    erased = true;
                    break;
                }
            }
            if (!erased) {
                ++outerIter;
            }
        }
    }


    /**
     * Resolves pattern of the form (a binOp !a) to (true) or false depending on the parameters.
     *
     * @tparam ResolvedValue Value that replaces the pattern.
     * @tparam SetType Type of the expression set.
     * @param expressions Expressions to check.
     */
    template<bool ResolvedValue, class SetType>
    void reduceNegations(SetType &expressions) {
        for (auto itrOuter = expressions.begin(); itrOuter != expressions.end();) {
            bool erased = false;
            auto negation = Not(*itrOuter);
            for (auto itrInner = expressions.begin(); itrInner != expressions.end(); ++itrInner) {

                if (*itrInner == *itrOuter) {
                    continue;
                }

                if (**itrInner == negation) {
                    expressions.emplace(std::make_shared<Constant>(ResolvedValue));
                    expressions.erase(itrInner);
                    itrOuter = expressions.erase(itrOuter);
                    erased = true;
                    break;
                }
            }
            if (!erased) {
                ++itrOuter;
            }
        }
    }

    /**
     * Resolves pattern of the form (a & ( a | b )) to (a) (and dual).
     *
     * @tparam AbsorptionType Whether we resolve for And or Or expressions.
     * @tparam SetType Type of expression set.
     * @param expressions Set of expressions to check.
     */
    template<class AbsorptionType, class SetType>
    void absorption(SetType &expressions) {
        for (auto itrOuter = expressions.begin(); itrOuter != expressions.end(); ++itrOuter) {
            for (auto itrInner = expressions.begin(); itrInner != expressions.end();) {
                bool erased = false;
                // do not compare expr against itself
                if (*itrInner == *itrOuter) {
                    ++itrInner;
                    continue;
                }
                // Found an AbsorptionType
                if (auto absorptionTypeInnerExpr = std::dynamic_pointer_cast<AbsorptionType>(*itrInner)) {

                    // If we have an expr of AbsorptionType one must be the subset of the other
                    if (auto absorptionTypeOuterExpr = std::dynamic_pointer_cast<AbsorptionType>(*itrOuter)) {
                        if (std::includes(absorptionTypeInnerExpr->begin(), absorptionTypeInnerExpr->end(),
                                          absorptionTypeOuterExpr->begin(), absorptionTypeOuterExpr->end(),
                                          NaryInterface::SharedPtrExprCompare())) {
                            erased = true;
                            itrInner = expressions.erase(itrInner);
                            break;
                        }
                    }
                    else {
                        // else check if the itrOuter is contained in itrInner
                        for (const auto &exp : absorptionTypeInnerExpr->getExpressions()) {
                            // Absorption can be applied
                            if (*exp == **itrOuter) {
                                erased = true;
                                itrInner = expressions.erase(itrInner);
                                break;
                            }
                        }
                    }
                }
                if (!erased) {
                    ++itrInner;
                }
            }
        }
    }
}
