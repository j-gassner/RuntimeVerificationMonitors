#pragma once


#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>

#include "ExpressionTree/Expression.h"
#include "Formula/Formula.h"
#include "ExpressionTree/Nary/NaryInterface.h"

/**
 * Functions for the Quine-McCluskey algorithm.
 */
namespace QMC {

    /**
     * Combines string vectors if they only differ by one digit at index.
     * @param v1
     * @param v2
     * @param index
     * @return Vector combining v1 and v2.
     */
    [[nodiscard]] std::vector<std::string>
    combineStringVectors(const std::vector<std::string> &v1, const std::vector<std::string> &v2, size_t index);

    /**
     * Checks if two vector can be combined, i.e., differ by only one digit.
     * @param vec1
     * @param vec2
     * @return True if they can be combined, false otherwise.
     */
    [[nodiscard]] int canBeCombined(const std::vector<std::string> &vec1, const std::vector<std::string> &vec2);

    /**
     * Transforms a bool vector into a string vector.
     * @param boolVec
     * @return string vector.
     */
    [[nodiscard]] std::vector<std::string> booltoStringVector(const std::vector<bool> &boolVec);

    /**
     * Reduces a boolean formula using distributivity.
     * @param formula
     * @return Reduced formula.
     */
    [[nodiscard]] Formula reduceBoolFormula(const Formula &formula);

    /**
     * Apply distributivity in the form of (a OriginalType (b DistributiveType c)) <-> ((a DistributiveType b) OriginalType (a DistributiveType c)).
     *
     * @tparam OriginalType First operand for distributivity (e.g. And, Or)
     * @tparam DistributiveType Second operand for distributivity (e.g. Or, And)
     * @param expr
     * @return
     */
    template<class OriginalType, class DistributiveType>
    [[nodiscard]] std::shared_ptr<Expression> distributivityExpand(const std::shared_ptr<Expression> &expr) {
        auto originalExpr = std::dynamic_pointer_cast<OriginalType>(expr);

        // Check if there are only predicates bc then there is nothing to do
        bool onlyAtomics = true;
        for (const auto &originalExprItr : *originalExpr) {
            if (!std::dynamic_pointer_cast<Atomic>(originalExprItr) and
                !std::dynamic_pointer_cast<Not>(originalExprItr)) {
                onlyAtomics = false;
                break;
            }
        }
        if (onlyAtomics) {
            return expr;
        }

        // As long as there are expressions to combine combine them
        while (originalExpr->getExpressions().size() > 1) {
            // Get two expressions to combine
            auto andExprItr = originalExpr->begin();
            std::array<typename OriginalType::SetType_T, 2> sets;

            // Fill sets
            for (size_t i = 0; i < sets.size(); ++i) {
                if (auto atomicExpr = std::dynamic_pointer_cast<Atomic>(*andExprItr)) {
                    sets[i] = {atomicExpr};
                }
                else if (auto notExpr = std::dynamic_pointer_cast<Not>(*andExprItr)) {
                    sets[i] = {notExpr};
                }
                else if (auto naryExpr = std::dynamic_pointer_cast<NaryInterface>(*andExprItr)) {
                    sets[i] = {naryExpr->begin(), naryExpr->end()};
                }
                else {
                    throw std::runtime_error(
                            "QMC::distributive() : A child of originalExpr is neither atomic nor nary!");
                }
                andExprItr = originalExpr->erase(andExprItr);
                // If first element was atomic second must not be an atomic
                if (i == 0 && sets[0].size() == 1) {
                    // Search for non atomic
                    while (std::dynamic_pointer_cast<Atomic>(*andExprItr)) {
                        ++andExprItr;
                    }
                }
            }

            typename DistributiveType::SetType_T combinedSet;
            for (auto &sOuter : sets[0]) {
                for (auto &sInner : sets[1]) {
                    combinedSet.emplace(
                            std::make_shared<OriginalType>(typename OriginalType::SetType_T{sOuter, sInner}));
                }
            }

            originalExpr->addExpression(std::make_shared<DistributiveType>(combinedSet));
        }
        return originalExpr;
    }

    /**
     * Apply distributivity in the form of ((a DistributiveType b) OriginalType (a DistributiveType c)) <-> (a OriginalType (b DistributiveType c)).
     *
     * @tparam OriginalType First operand for distributivity (e.g. And, Or)
     * @tparam DistributiveType Second operand for distributivity (e.g. Or, And)
     * @param expr Expression.
     * @return New distributed expression.
     */
    template<class OriginalType, class DistributiveType>
    [[nodiscard]] std::shared_ptr<Expression> distributivityReduce(const std::shared_ptr<Expression> &expr) {
        auto originalExpr = std::dynamic_pointer_cast<OriginalType>(expr);
        auto expressions = originalExpr->getExpressions();
        typename DistributiveType::SetType_T newSet;
        for (auto itrOuter = expressions.begin(); itrOuter != expressions.end();) {
            bool eraseOuter = false;
            auto firstExpr = std::dynamic_pointer_cast<DistributiveType>(*itrOuter);
            // We only care about expressions of DistributiveType
            if (not firstExpr) {
                ++itrOuter;
                continue;
            }
            for (auto itrInner = itrOuter; itrInner != expressions.end();) {
                bool erased = false;
                // do not compare expr against itself
                if (*itrInner == *itrOuter) {
                    ++itrInner;
                    continue;
                }
                // If we have two exprs of DistributiveType check if there is an intersection
                if (auto secondExpr = std::dynamic_pointer_cast<DistributiveType>(*itrInner)) {
                    // Sets distr should be applied to
                    typename DistributiveType::SetType_T firstSet(firstExpr->getExpressions().begin(),
                                                                  firstExpr->getExpressions().end());
                    typename DistributiveType::SetType_T secondSet(secondExpr->getExpressions().begin(),
                                                                   secondExpr->getExpressions().end());
                    typename DistributiveType::SetType_T intersection;
                    std::set_intersection(firstSet.begin(), firstSet.end(),
                                          secondSet.begin(), secondSet.end(),
                                          std::inserter(intersection, intersection.begin()),
                                          NaryInterface::SharedPtrExprCompare());
                    // There is an intersection
                    if (!intersection.empty()) {
                        auto intersectionExpr = NaryInterface::makeNary<DistributiveType>(intersection);

                        // Erase intersection from both sets
                        typename DistributiveType::SetType_T firstSetDiff;
                        typename DistributiveType::SetType_T secondSetDiff;
                        std::set_difference(firstSet.begin(), firstSet.end(), intersection.begin(), intersection.end(),
                                            std::inserter(firstSetDiff, firstSetDiff.begin()),
                                            NaryInterface::SharedPtrExprCompare());
                        std::set_difference(secondSet.begin(), secondSet.end(), intersection.begin(),
                                            intersection.end(), std::inserter(secondSetDiff, secondSetDiff.begin()),
                                            NaryInterface::SharedPtrExprCompare());
                        // Create expression from both sets
                        auto firstSetExpr = std::make_shared<DistributiveType>(firstSetDiff);
                        auto secondSetExpr = std::make_shared<DistributiveType>(secondSetDiff);
                        typename OriginalType::SetType_T distrExpandSet{firstSetExpr, secondSetExpr};
                        auto differenceExpr = std::make_shared<OriginalType>(distrExpandSet);
//                        // Merge both sets
//                        typename DistributiveType::SetType_T merged;
//                        std::set_union(firstExpr->getExpressions().begin(), firstExpr->getExpressions().end(),
//                                       secondExpr->getExpressions().begin(), secondExpr->getExpressions().end(),
//                                       std::inserter(merged, merged.begin()), NaryInterface::SharedPtrExprCompare());
//
//                        // Erase intersection from merged set
//                        typename OriginalType::SetType_T difference;
//                        std::set_difference(merged.begin(), merged.end(), intersection.begin(), intersection.end(),
//                                            std::inserter(difference, difference.begin()),
//                                            NaryInterface::SharedPtrExprCompare());
                        // Build new expr
                        auto distrExpand = distributivityExpand<OriginalType, DistributiveType>(differenceExpr);

//                        auto differenceExpr = std::make_shared<OriginalType>(difference);
                        // Final result
                        typename DistributiveType::SetType_T distributiveSet{intersectionExpr, distrExpand};
                        auto distributivity = std::make_shared<DistributiveType>(distributiveSet);
                        newSet.emplace(distributivity);
                        erased = true;
                        eraseOuter = true;
                        itrInner = expressions.erase(itrInner);
                    }
                }
                if (!erased) {
                    ++itrInner;
                }
            }
            if (eraseOuter) {
                itrOuter = expressions.erase(itrOuter);
            }
            else {
                ++itrOuter;
            }
        }
        return std::make_shared<DistributiveType>(newSet);
    }


    [[nodiscard]] std::shared_ptr<Expression> idempotence(const std::shared_ptr<Expression> &expr);

    [[nodiscard]] std::shared_ptr<Expression> absorption(const std::shared_ptr<Expression> &expr);

    [[nodiscard]] std::shared_ptr<Expression> minimize(const std::shared_ptr<Expression> &expr);

    [[nodiscard]] std::shared_ptr<Expression> assoc(const std::shared_ptr<Expression> &expr);

    [[nodiscard]]Formula minimize(Formula &formula);

    [[nodiscard]] std::string
    nameToAtomics(const std::string &name, const std::map<std::string, std::vector<std::string>> &primeTermsRelevant,
                  const std::set<std::string> &atomics);

    template<class F>
    [[nodiscard]] std::shared_ptr<Expression> apply(const std::shared_ptr<Expression> &expr, F f) {
        auto ret = f(expr);
        if (ret->getLeft()) {
            ret->setLeft(apply(ret->getLeft(), f));
        }
        if (ret->getRight()) {
            ret->setRight(apply(ret->getRight(), f));
        }
        return ret;
    }
};



