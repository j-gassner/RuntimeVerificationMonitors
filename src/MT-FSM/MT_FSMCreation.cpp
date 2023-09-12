#include <algorithm>
#include <iostream>
#include "QMC/QMC.h"
#include "Trace/EventGenerator.h"
#include "EventConsuming/EventConsuming.h"
#include "MT_FSMCreation.h"
#include "Rewriting/BasicRewriteVisitor.h"
#include "Utils/Utils.h"
#include "ExpressionTree/Atomic/Atomic.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Nary/Bool/Or.h"
#include "ExpressionTree/Binary/Bool/Equivalence.h"
#include "StateMT_FSM.h"

bool MT_FSMCreation::valid(Formula &formula) {
    std::set<Formula> states{formula};
    return valid(formula, states);
}

// Fig 6
bool MT_FSMCreation::valid(Formula &formula, std::set<Formula> &states) {
    auto atomics = Utils::getAtomics(formula.getExpr(), {});
    auto numberOfAtomics = Utils::getNumberOfAtomics(formula.getExpr());

    // Only constants
    if (numberOfAtomics == 0) {
        if (auto constant = std::dynamic_pointer_cast<Constant>(formula.getExpr())) {
            return constant->getValue();
        }
        else if (auto eq = std::dynamic_pointer_cast<Equivalence>(formula.getExpr())) {
            if ((*(eq->getLeft()) == *(eq->getRight()))) {
                return true;
            }
                // TODO: better way: resolve the formula end return the result
            else if (formula.to_string() == "(false <-> true)" or formula.to_string() == "(true <-> false)") {
                return false;
            }
        }
        // Should never be reached
        throw std::runtime_error("MT_FSMCreation.cpp::valid() : formula has no predicates and is not handled!");
    }

    EventGenerator gen(numberOfAtomics);

    for (auto event = gen.getEventVector(); gen.hasNext(); event = gen.getNext()) {
        // Terminal eventMap
        auto traceNonTerminal = Utils::boolVectorToTrace(atomics, event, true);
        if (EventConsuming::eventConsumingFuture(formula, traceNonTerminal).getExpr()->isConstFalse()) {
            return false;
        }
        // Nonterminal eventMap
        auto traceTerminal = Utils::boolVectorToTrace(atomics, event, false);
        Formula f = EventConsuming::eventConsumingFuture(formula, traceTerminal);
        //br.rewrite(f);

        auto[_, inserted] = states.emplace(f);
        if (inserted and not valid(f, states)) {
            return false;
        }
    }
    return true;
}

MultiTransition MT_FSMCreation::merge(MultiTransition &mt_1, MultiTransition mt_2) {
    BasicRewriteVisitor br;

    std::map<Formula, size_t> mergedTransitions;

    // Keeps track of every transition in mt_2 if it was already merged
    std::vector<bool> mt_2TransitionMerged(mt_2.getTransitions().size());

    // First check mt_1 -> mt_2
    for (auto &[formula1, state1] : mt_1.getTransitions()) {
        // Check if state1 is in mt_2
        bool stateFound = false;
        size_t mt_2Id = 0;
        for (auto &[formula2, state2] : mt_2.getTransitions()) {
            if (state1 == state2) {
                // Formula1 OR formula2
                Formula mergedFormula(std::make_shared<Or>(Or::SetType_T{formula1.getExpr(), formula2.getExpr()}));
                br.rewrite(mergedFormula);
                mergedTransitions.emplace(QMC::reduceBoolFormula(mergedFormula), state1);
                stateFound = true;
                mt_2TransitionMerged[mt_2Id] = true;
                break;
            }
            ++mt_2Id;
        }
        if (not stateFound) {
            auto formulaNonConst = Formula(formula1);
            br.rewrite(formulaNonConst);
            mergedTransitions.emplace(QMC::reduceBoolFormula(formulaNonConst), state1);

        }
    }

    // Then check mt_2 -> mt_1. There will be no new merged formulae so we only need to insert new ones.
    size_t mt_2Id = 0;
    for (auto &[formula2, state2] : mt_2.getTransitions()) {
        // check if state2 is in mt_1
        if (not mt_2TransitionMerged[mt_2Id]) {
            auto formulaNonConst = Formula(formula2);
            br.rewrite(formulaNonConst);
            mergedTransitions.emplace(QMC::reduceBoolFormula(formulaNonConst), state2);
        }
        ++mt_2Id;
    }

    return MultiTransition(mergedTransitions);
}

// Fig 5
void
MT_FSMCreation::formulaToMT_FSM(const Formula &formula, std::vector<StateMT_FSM> &states, bool past) {
    //std::cout << formula.to_string() << std::endl;
    MultiTransition mtTerminal({});
    MultiTransition mtNonTerminal({});

    auto atomics = Utils::getAtomics(formula.getExpr(), {});
    auto numberOfAtomics = Utils::getNumberOfAtomics(formula.getExpr());
    // All possible events
    EventGenerator gen(numberOfAtomics);
    for (auto event = gen.getEventVector(); gen.hasNext(); event = gen.getNext()) {
        auto currentEvent = Utils::boolVectorToEvent(atomics, event, false);
        auto conjunction = Utils::eventToFormula(currentEvent); //7

        auto traceTerminal = Utils::boolVectorToTrace(atomics,
                                                      event,
                                                      true);
        auto formulaEventConsumingTerminal = EventConsuming::eventConsumingFuture(formula,
                                                                                  traceTerminal);

        // Sanity check
        if (not std::dynamic_pointer_cast<Constant>(formulaEventConsumingTerminal.getExpr())) {
            throw std::runtime_error(
                    "MT_FSMCreation::formulaToMT_FSM() EventConsuming did not return a Constant on terminal event");
        }
        // Is true or false
        size_t evaluation = formulaEventConsumingTerminal.getExpr()->isConstTrue();

        MultiTransition currentMT = MultiTransition({{conjunction, evaluation}});
        mtTerminal = merge(currentMT, mtTerminal);

        Formula formulaEventConsuming(nullptr);
        if (!past) {
            auto traceNonTerminal = Utils::boolVectorToTrace(atomics, event,
                                                             false);
            formulaEventConsuming = EventConsuming::eventConsumingFuture(formula,
                                                                         traceNonTerminal);
        }
        else {
            auto trace = Utils::boolVectorToTrace(atomics, event, false);
            formulaEventConsuming = EventConsuming::eventConsumingPast(formula, trace);
        }
        // 10 Search for equivalent formula
        bool eqFormulaExists = false;
        for (size_t stateId = 0; stateId < states.size(); ++stateId) {
            auto equivalence = Formula(std::make_shared<Equivalence>(formulaEventConsuming.getExpr(),
                                                                     states[stateId].getFormula().getExpr()));
            //TODO: add shortcut: if string representation of formulaEventConsuming and states[i] is equal then the equivalence is valid (inverse obviously not)

            if (valid(equivalence)) {
                currentMT = MultiTransition({{conjunction, stateId}});
                mtNonTerminal = merge(currentMT, mtNonTerminal);
                eqFormulaExists = true;
                break;
            }
        }
        if (not eqFormulaExists) {

            // Check if this formula already exists in states since they should be unique
            bool found = false;
            for (const auto &state: states) {
                if (state.getFormula() == formulaEventConsuming) {
                    currentMT = MultiTransition({{conjunction, state.getId()}});
                    found = true;
                    break;
                }
            }
            // Not found so add formula to states
            if (not found) {
                // Add next state
                StateMT_FSM newState(states.size(), formulaEventConsuming);
                states.push_back(newState);

                currentMT = MultiTransition({{conjunction, states.size() - 1}});

                mtNonTerminal = merge(currentMT, mtNonTerminal);

                formulaToMT_FSM(formulaEventConsuming, states, past);
            }
        }
    }
    auto &transitionsNT = mtNonTerminal.getTransitions();
    auto &transitionsT = mtTerminal.getTransitions();
    if (transitionsNT.size() == 1 and transitionsT.size() == 1) {

        auto formulaTrue = Formula(std::make_shared<Constant>(true));
        auto propositionNT = transitionsNT.find(formulaTrue);
        auto propositionT = transitionsT.find(formulaTrue);
        if (propositionNT != transitionsNT.end() and
            propositionT != transitionsT.end()) {

            // Replace formula in MT
            auto newFormula = propositionT->first;
            auto stateTmp = propositionT->second;
            transitionsNT.erase(formulaTrue);
            transitionsNT.emplace(newFormula, stateTmp);
        }
    }

    auto currentStateIter = std::find_if(states.begin(), states.end(),
                                         [&](const StateMT_FSM &s) { return s.getFormula() == formula; });
    auto &currentState = states[std::distance(states.begin(), currentStateIter)];
    currentState.setTerminal(mtTerminal);
    currentState.setNonTerminal(mtNonTerminal);

}

// Wrapper function
MT_FSM MT_FSMCreation::formulaToMT_FSM(const Formula &formula, bool past) {
    auto formulaCopy = formula.deepCopy();
    // Only a constant
    if (auto constant = std::dynamic_pointer_cast<Constant>(formula.getExpr())) {
        StateMT_FSM singleState(constant->getValue(), formula);
        std::set<std::string> empty{};
        std::vector<StateMT_FSM> vector{singleState};
        return MT_FSM(empty, formulaCopy, vector);
    }
    auto formulaFalse = Formula(std::make_shared<Constant>(false));
    auto formulaTrue = Formula(std::make_shared<Constant>(true));
    StateMT_FSM stateFalse(0, formulaFalse);
    StateMT_FSM stateTrue(1, formulaTrue);
    StateMT_FSM stateFirst(2, formulaCopy);
    std::vector<StateMT_FSM> states{stateFalse, stateTrue, stateFirst};
    auto atomics = Utils::getAtomics(formula.getExpr());
    formulaToMT_FSM(formulaCopy, states, past);
    return MT_FSM{atomics, formulaCopy, states};
}
