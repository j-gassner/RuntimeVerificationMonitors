#pragma once


#include <set>
#include <vector>
#include "Formula/Formula.h"
#include "StateBTT_FSM.h"

/**
 * Class representing a Binary Transition Tree Finite State Machine (BTT-FSM).
 */
class BTT_FSM {
private:
    Formula formula;
    std::vector<StateBTT_FSM> states;

public:
    /**
     * Constructor for a BTT-FSM.
     * @param formula Forumla that we want the BTT-FSM for.
     * @param states Vector of StateBTT_FSM.
     */
    BTT_FSM(Formula formula, std::vector<StateBTT_FSM> states);

    /**
     * Returns the formula the BTT-FSM was constrcuted for.
     * @return Formula.
     */
    [[nodiscard]] const Formula &getFormula() const;

    /**
     * Returns a vector of all states in the BTT-FSM.
     * @return Vector of StateBTT_FSM.
     */
    [[nodiscard]] const std::vector<StateBTT_FSM> &getStates() const;

    /**
     * Setter for formula.
     * @param formula
     */
    void setFormula(const Formula &formula);

    /**
     * Setter for state vector.
     * @param states
     */
    void setStates(const std::vector<StateBTT_FSM> &states);

    /**
     * to_string() function.
     * @return String representation of the BTT-FSM.
     */
    [[nodiscard]] std::string to_string() const;
};



