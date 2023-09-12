#include "MT_FSM.h"

MT_FSM::MT_FSM(std::set<std::string> &atomics, Formula &formula, std::vector<StateMT_FSM> &states) : atomics(
        std::move(atomics)),
                                                                                                     formula(std::move(
                                                                                                             formula)),
                                                                                                     states(std::move(
                                                                                                             states)) {}

//TODO check if empty
std::string MT_FSM::to_string() const {
    std::stringstream res;
    res << "Formula: " << std::endl << formula.to_string() << std::endl;
    res << "Atomics:" << std::endl << "[" << *atomics.begin();
    for (auto it = std::next(atomics.begin()); it != atomics.end(); ++it) {

        res << ", " << *it;
    }
    res << "]" << std::endl;
    for (const auto &state : states) {
        res << "Id: " << std::endl << state.getId() << std::endl;
        res << "Non-terminal transitions: " << std::endl << state.getNonTerminal().to_string() << std::endl;
        res << "Terminal transitions: " << std::endl << state.getTerminal().to_string() << std::endl;
    }

    return res.str();
}

const std::set<std::string> &MT_FSM::getAtomics() const {
    return atomics;
}

void MT_FSM::setAtomics(const std::set<std::string> &atomics) {
    MT_FSM::atomics = atomics;
}

const Formula &MT_FSM::getFormula() const {
    return formula;
}

void MT_FSM::setFormula(const Formula &formula) {
    MT_FSM::formula = formula;
}

const std::vector<StateMT_FSM> &MT_FSM::getStates() const {
    return states;
}

void MT_FSM::setStates(const std::vector<StateMT_FSM> &states) {
    MT_FSM::states = states;
}
