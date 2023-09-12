#pragma once


#include <vector>
#include "MultiTransition.h"
#include "MT_FSM.h"
#include "StateMT_FSM.h"

namespace MT_FSMCreation {

    /**
     * Checks for a given formula and a set of states if formula returns true for every form it can evolve into.
     * @param formula
     * @return
     */
    [[nodiscard]] bool valid(Formula &formula);

    /**
     * Helper for recursion with additional argument.
     * @param formula
     * @param states
     * @return True if valid, false otherwise.
     */
    [[nodiscard]] bool valid(Formula &formula, std::set<Formula> &states);

    /**
     * Merges two multi-transistions if possible.
     * @param mt_1 First multi-transistion.
     * @param mt_2 Second multi_transition.
     * @return New merged MT.
     */
    [[nodiscard]] MultiTransition merge(MultiTransition &mt_1, MultiTransition mt_2);

    /**
     * Helper for formulaToMT_FSM().
     * @param formula
     * @param states
     * @param past True if formula is in PLTLf.
     */
    void formulaToMT_FSM(const Formula &formula, std::vector<StateMT_FSM> &states, bool past);

    /**
     * Constructs an MT-FSM* from a given formula.
     * @param formula
     * @param past True if formula is in PLTLf.
     * @return MT-FSM*.
     */
    [[nodiscard]] MT_FSM formulaToMT_FSM(const Formula &formula, bool past);

};



