#include "StateBTT_FSM.h"
#include "Decision.h"

#include <utility>
#include <sstream>
#include <Utils/Utils.h>

StateBTT_FSM::StateBTT_FSM(size_t id, std::shared_ptr<Node> nonTerminal, std::shared_ptr<Node> terminal)
        : id(id), nonTerminal(std::move(nonTerminal)), terminal(std::move(terminal)) {}

StateBTT_FSM::StateBTT_FSM(size_t id) : id(id) {}

size_t StateBTT_FSM::getId() const {
    return id;
}

void StateBTT_FSM::setId(size_t id) {
    StateBTT_FSM::id = id;
}

const std::shared_ptr<Node> &StateBTT_FSM::getNonTerminal() const {
    return nonTerminal;
}

void StateBTT_FSM::setNonTerminal(const std::shared_ptr<Node> &nonTerminal) {
    StateBTT_FSM::nonTerminal = nonTerminal;
}

const std::shared_ptr<Node> &StateBTT_FSM::getTerminal() const {
    return terminal;
}

void StateBTT_FSM::setTerminal(const std::shared_ptr<Node> &terminal) {
    StateBTT_FSM::terminal = terminal;
}

size_t StateBTT_FSM::nextState(Event &event) {
    std::shared_ptr<Decision> decision;
    // Terminal
    if (event.isTerminal()) {
        // It's always a Decision
        decision = std::dynamic_pointer_cast<Decision>(terminal);
    }
        // Non-terminal
    else {
        decision = std::dynamic_pointer_cast<Decision>(nonTerminal);
    }
    return nextState(event, decision);
}

size_t StateBTT_FSM::nextState(Event &event, const std::shared_ptr<Decision> &decision) {
    std::shared_ptr<Node> next;
    // Predicate is true
    if (Utils::evaluateBooleanExpression(decision->getPredicate(), event.getEventMapRef())) {
        next = decision->getLeft();
    }
    else {
        next = decision->getRight();
    }
    // If it's not a state we have to go further down the BTT
    if (auto nextDecision = std::dynamic_pointer_cast<Decision>(next)) {
        return nextState(event, nextDecision);
    }
        // It's a state
    else {
        auto nextState = std::dynamic_pointer_cast<StateBTT_FSM>(next);
        return nextState->id;
    }
}

std::string StateBTT_FSM::to_string() const {
    std::stringstream res;
    if (!id) {
        res << "false" << std::endl;
    }
    else if (id == 1) {
        res << "true" << std::endl;
    }
    else {
        res << "Id: " << id << std::endl;
        // True and false don't have transitions
        res << "Non-terminal: " << nonTerminal->to_string() << std::endl;
        res << "Terminal: " << terminal->to_string() << std::endl;
    }

    return res.str();
}

