#include <iostream>
#include "MT_FSMEvaluation.h"
#include "MT_FSM.h"
#include "ExpressionTree/Atomic/Constant.h"

bool MT_FSMEvaluation::evaluateMT_FSM(const MT_FSM &mtFsm, Trace &trace, bool past) {
    // Nothing to do here
//    if (auto constant = std::dynamic_pointer_cast<Constant>(formula.getExpr())) {
//        return constant->getValue();
//    }
//    auto formulaCopy = formula.deepCopy();
//    MT_FSM mtFsm = MT_FSMCreation::formulaToMT_FSM(formulaCopy, past);
    const auto &states = mtFsm.getStates();

    // First two states are true and false
    auto currentState = states[2];

    if (past) {
        trace.setTerminalEvent(false);
    }

    for (size_t i = 0; i < trace.getLength(); ++i) {
        // If past then access in inverted order
        size_t eventIndex = past ? trace.getLength() - 1 - i : i;
        size_t nextState = currentState.nextState(trace.getEvent(eventIndex));
        if (!nextState) {
            //std::cout << "Formula violated in event " << eventIndex << std::endl;
            return false;
        }
        if (nextState == 1) {
            //std::cout << "Formula satisfied in event " << eventIndex << std::endl;
            return true;
        }
        currentState = states[nextState];
    }
    return false;
}

