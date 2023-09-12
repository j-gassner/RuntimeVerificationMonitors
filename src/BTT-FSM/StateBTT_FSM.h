#pragma once

#include <cstdlib>
#include <string>
#include <memory>
#include "Trace/Event.h"
#include "Node.h"
#include "Decision.h"

/**
 * Models a Node in a BTT which is a state, i.e. there is no left or right as in Decision. It contains an Id and the (non-)terminal BTT for this state.
 */
class StateBTT_FSM : public Node {
private:
    size_t id;
    std::shared_ptr<Node> nonTerminal;
    std::shared_ptr<Node> terminal;

public:
    /**
     * Constructor.
     * @param id Id.
     * @param nonTerminal BTT for non-terminal events.
     * @param terminal BTT for terminal events.
     */
    StateBTT_FSM(size_t id, std::shared_ptr<Node> nonTerminal, std::shared_ptr<Node> terminal);

    /**
     * Constructor, terminal and nonTerminal stay empty.
     * @param id Id.
     */
    explicit StateBTT_FSM(size_t id);

    /**
     * Getter for id.
     * @return Id.
     */
    [[nodiscard]] size_t getId() const;

    /**
     * Getter for nonTerminal.
     * @return BTT for non-terminal event.
     */
    [[nodiscard]] const std::shared_ptr<Node> &getNonTerminal() const;

    /**
     * Getter for terminal.
     * @return BTT for terminal event.
     */
    [[nodiscard]] const std::shared_ptr<Node> &getTerminal() const;

    /**
     * Setter for id.
     * @param id Id.
     */
    void setId(size_t id);

    /**
     * Setter for nonTerminal.
     * @param nonTerminal BTT for non-terminal event.
     */
    void setNonTerminal(const std::shared_ptr<Node> &nonTerminal);

    /**
     * Setter for terminal.
     * @param nonTerminal BTT for terminal event.
     */
    void setTerminal(const std::shared_ptr<Node> &terminal);

    /**
     * Decides which state is next during evaluation.
     * @param event Current event to be evaluated.
     * @return Id of state after event has been evaluated.
     */
    [[nodiscard]] size_t nextState(Event &event);

    /**
     * Helper function for nextState(Event& event).
     * @param event Current event to be evaluated.
     * @return Id of state after event has been evaluated.
     */
    [[nodiscard]] size_t nextState(Event &event, const std::shared_ptr<Decision> &decision);

    /**
     * to_string() for StateBTT_FSM.
     * @return String representation of this StateBTT_FSM.
     */
    [[nodiscard]] std::string to_string() const override;
};



