#pragma once


#include "Formula/Formula.h"
#include "MultiTransition.h"

/**
 * State of an MT-FSM.
 */
class StateMT_FSM {
private:
    size_t id;
    MultiTransition nonTerminal = MultiTransition({});
    MultiTransition terminal = MultiTransition({});
    Formula formula;

public:
    /**
     * Constructor.
     * @param id Id.
     * @param nonTerminal Non-terminal transitions.
     * @param terminal Terminal transitions.
     * @param formula Formula.
     */
    StateMT_FSM(size_t id, MultiTransition nonTerminal, MultiTransition terminal, const Formula &formula);

    /**
     * Constructor.
     * @param id Id.
     * @param formula Formula.
     */
    StateMT_FSM(size_t id, const Formula &formula);

    /**
     * Getter for id.
     * @return id.
     */
    [[nodiscard]] size_t getId() const;

    /**
     * Setter for id.
     * @param id
     */
    void setId(size_t id);

    /**
     * Getter for non-terminal transitions.
     * @return nonTerminal.
     */
    [[nodiscard]] const MultiTransition getNonTerminal() const;

    /**
     * Getter for terminal transitions.
     * @return terminal.
     */
    [[nodiscard]] const MultiTransition &getTerminal() const;

    /**
     * Getter for formula.
     * @return formula.
     */
    [[nodiscard]] const Formula &getFormula() const;

    /**
     * Setter for non-terminal transitions.
     * @param nonTerminal
     */
    void setNonTerminal(const MultiTransition &nonTerminal);

    /**
     * Setter for terminal transitions.
     * @param terminal
     */
    void setTerminal(const MultiTransition &terminal);

    /**
     * Setter for formula.
     * @param formula
     */
    void setFormula(const Formula &formula);

    /**
     * Next state according to an event.
     * @param event
     * @return Next state.
     */
    [[nodiscard]] size_t nextState(Event &event);

    /**
     * To_string.
     * @return String representation of the state.
     */
    [[nodiscard]] std::string to_string() const;
};



