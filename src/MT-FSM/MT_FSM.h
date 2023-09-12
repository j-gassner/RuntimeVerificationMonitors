#pragma once

#include <memory>
#include <utility>
#include <vector>
#include "Trace/Trace.h"
#include "Formula/Formula.h"
#include "StateMT_FSM.h"

/**
 * Class to manage an MT-FSM*.
 */
class MT_FSM {
private:
    std::set<std::string> atomics;
    Formula formula;
    std::vector<StateMT_FSM> states;
public:
    /**
     * Constructor.
     * @param atomics Predicates.
     * @param formula Formula.
     * @param states Vector of states.
     */
    MT_FSM(std::set<std::string> &atomics, Formula &formula, std::vector<StateMT_FSM> &states);

    /**
     * Getter for atomics.
     * @return atomics.
     */
    [[nodiscard]] const std::set<std::string> &getAtomics() const;

    /**
     * Setter for atomics.
     * @param atomics
     */
    void setAtomics(const std::set<std::string> &atomics);

    /**
     * Getter for formula.
     * @return formula.
     */
    [[nodiscard]] const Formula &getFormula() const;

    /**
     * Setter for formula.
     * @param formula
     */
    void setFormula(const Formula &formula);

    /**
     * Getter for states.
     * @return states.
     */
    [[nodiscard]] const std::vector<StateMT_FSM> &getStates() const;

    /**
     * Setter for states.
     * @param states
     */
    void setStates(const std::vector<StateMT_FSM> &states);

    /**
     * String representation of the MT-FSM*.
     * @return String representation of the MT-FSM*.
     */
    [[nodiscard]] std::string to_string() const;

};



