#include "BTT_FSM.h"

#include <utility>

BTT_FSM::BTT_FSM(Formula formula, std::vector<StateBTT_FSM> states) : formula(std::move(formula)),
                                                                      states(std::move(states)) {}

const Formula &BTT_FSM::getFormula() const {
    return formula;
}

void BTT_FSM::setFormula(const Formula &formula) {
    BTT_FSM::formula = formula;
}

const std::vector<StateBTT_FSM> &BTT_FSM::getStates() const {
    return states;
}

void BTT_FSM::setStates(const std::vector<StateBTT_FSM> &states) {
    BTT_FSM::states = states;
}

std::string BTT_FSM::to_string() const {
    std::stringstream res;
    res << "BTT-FSM for " << formula.to_string() << std::endl;
    for (const auto &state :states) {
        res << state.to_string();
    }
    return res.str();
}
