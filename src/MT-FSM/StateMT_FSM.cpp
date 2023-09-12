#include <utility>
#include "Utils/Utils.h"
#include "StateMT_FSM.h"

StateMT_FSM::StateMT_FSM(size_t id, MultiTransition nonTerminal, MultiTransition terminal, const Formula &formula)
        : id(id), nonTerminal(std::move(nonTerminal)), terminal(std::move(terminal)), formula(formula) {}

StateMT_FSM::StateMT_FSM(size_t id, const Formula &formula) : id(id), formula(formula) {}

size_t StateMT_FSM::getId() const {
    return id;
}

void StateMT_FSM::setId(size_t id) {
    StateMT_FSM::id = id;
}

const MultiTransition StateMT_FSM::getNonTerminal() const {
    return nonTerminal;
}

void StateMT_FSM::setNonTerminal(const MultiTransition &nonTerminal) {
    StateMT_FSM::nonTerminal = nonTerminal;
}

const MultiTransition &StateMT_FSM::getTerminal() const {
    return terminal;
}

void StateMT_FSM::setTerminal(const MultiTransition &terminal) {
    StateMT_FSM::terminal = terminal;
}

const Formula &StateMT_FSM::getFormula() const {
    return formula;
}

void StateMT_FSM::setFormula(const Formula &formula) {
    StateMT_FSM::formula = formula;
}

std::string StateMT_FSM::to_string() const {
    std::stringstream ret;
    ret << "Id: " << std::endl << id << std::endl;
    ret << "Non-terminal transitions: " << std::endl << nonTerminal.to_string() << std::endl;
    ret << "Terminal transitions: " << std::endl << terminal.to_string() << std::endl;
    return ret.str();
}

size_t StateMT_FSM::nextState(Event &event) {
    std::map<Formula, size_t> transitions;
    // Terminal
    if (event.isTerminal()) {
        transitions = terminal.getTransitions();
    }

        // Non-terminal
    else {
        transitions = nonTerminal.getTransitions();
    }

    for (const auto &transition : transitions) {
        if (Utils::evaluateBooleanExpression(transition.first.getExpr(), event.getEventMapRef())) {
            return transition.second;
        }
    }
    throw std::runtime_error("StateMT_FSM::nextState() No next state could be found.");
}


