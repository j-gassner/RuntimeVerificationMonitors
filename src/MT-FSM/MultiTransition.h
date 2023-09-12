#pragma once


#include "Formula/Formula.h"

/**
 * Class representing a multi-transition.
 */
class MultiTransition {
private:
    // Outgoing transitions from state
    std::map<Formula, size_t> transitions;

public:
    /**
     * Constructor.
     * @param transitions
     */
    explicit MultiTransition(std::map<Formula, size_t> transitions);

    /**
     * Getter for transitions.
     * @return transitions.
     */
    [[nodiscard]] std::map<Formula, size_t> &getTransitions();

    /**
     * Const getter for transitions.
     * @return transitions.
     */
    [[nodiscard]] const std::map<Formula, size_t> &getTransitions() const;

    /**
     * To_string().
     * @return String representation of the MT.
     */
    [[nodiscard]] std::string to_string() const;

    /**
     * Evaluates next state according to an event.
     * @param eventMap
     * @return Next state in MT-FSM*.
     */
    [[nodiscard]] size_t evaluate(std::map<std::string, LazyBool> &eventMap) const;
};
