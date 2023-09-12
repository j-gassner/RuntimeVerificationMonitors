#pragma once

#include <algorithm>
#include "MT-FSM/StateMT_FSM.h"
#include "Formula/Formula.h"
#include "BTT_FSM.h"

/**
 * Encapsulates all functions needed to create a BTT-FSM from a formula.
 */
namespace BTT_FSMCreation {
    /**
     * Creates a BTT-FSM from a given formula.
     * @param formula Formula.
     * @param past True if formula is in pLTL.
     * @return BTT-FSM of formula.
     */
    BTT_FSM formulaToBTT_FSM(const Formula &formula, bool past);

    /**
     * Counts the frequency of all atomics in a MultiTransition.
     * @param multiTransition MultiTransition with formulas where atomic frequencies should be counted.
     * @return Map from string representation of each atomic to its frequency in the MultiTransition.
     */
    [[nodiscard]] std::map<std::string, size_t> getAtomicFrequencies(const MultiTransition &multiTransition);

    /**
     * Gives each atomic a weight w = (1/frequency) * cost. The higher the value the deeper the atomic is nested into the tree.
     * @param multiTransition MultiTransition.
     * @return Multimap weight -> atomic. This way the atomics are already ordered.
     */
    std::multimap<double, std::shared_ptr<Atomic>> getAtomicWeight(const MultiTransition &multiTransition);

    /**
     * Helper function. Flips a map and turns it into a multimap.
     * @param weights Map of atomic -> weight.
     * @return Multimap weight -> atomic.
     */
    std::multimap<double, std::shared_ptr<Atomic>>
    createWeightMultimap(const std::map<std::shared_ptr<Atomic>, double> &weights);

    /**
     * Replaces an atomic with a constant in a given formula. This is used to determine the next node in the BTT.
     * @param formula Formula.
     * @param atomic Atomic to be replaced.
     * @param constant Constant atomic is to be replaced with.
     * @return Formula with replaced atomic.
     */
    std::shared_ptr<Expression>
    replaceAtomicByConstant(const Formula &formula, const std::shared_ptr<Atomic> &atomic, bool constant);

    MultiTransition replaceAtomicInMultiTransition(const MultiTransition &multiTransition, const std::shared_ptr<Atomic> &atomic, bool constant);
    /**
     * Erases a given atomic from all formulas in a MultiTransition.
     * @param multiTransition MultiTransition.
     * @param atomic Atomic to be erased.
     * @return MultiTransition where formulas do not contain atomic anymore.
     */
    MultiTransition
    eraseAtomicFromFormula(const MultiTransition &multiTransition, const std::shared_ptr<Atomic> &atomic);

    /**
     * Used for building the BTT in each state. Checks which atomic (Node) should be added next by replacing each 
     * atomic with true/false in each formula of multiTransition. Only one atomic is replaced at a time.
     * If one of the formulas evaluates to true after this the replaced atomic as a Node is the next state.
     * @param multiTransition MultiTransition.
     * @param weights Weights of the atomics.
     * @return Node that should be added to the BTT next.
     */
    std::shared_ptr<Node>
    findNextNode(const MultiTransition &multiTransition, std::multimap<double, std::shared_ptr<Atomic>> &weights);

    /**
     * Flips a pair pair.
     * @tparam A First type.
     * @tparam B Second type.
     * @param pair Pair to be flipped.
     * @return Flipped pair.
     */
    template<typename A, typename B>
    std::pair<B, A> flip_pair(const std::pair<A, B> &pair) {
        return std::pair<B, A>(pair.second, pair.first);
    }

    /**
     * Flips a map.
     * @tparam A Key type.
     * @tparam B Value type.
     * @tparam Map Map type.
     * @tparam Args Additional arguments, optional.
     * @param map Map to be flipped.
     * @return Multimap with flipped key value pairs.
     */
    template<typename A, typename B, template<class, class, class...> class Map, class... Args>
    std::multimap<B, A> flip_map(const Map<A, B, Args...> &map) {
        std::multimap<B, A> flippedMap;
        std::transform(map.begin(), map.end(),
                       std::inserter(flippedMap, flippedMap.begin()),
                       flip_pair<A, B>);
        return flippedMap;
    }
}



