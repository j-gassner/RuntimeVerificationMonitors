#include <iostream>
#include "Utils/Utils.h"
#include "Rewriting/BasicRewriteVisitor.h"
#include "BTT_FSMCreation.h"
#include "MT-FSM/MT_FSMCreation.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Nary/NaryInterface.h"
#include "ExpressionTree/Unary/Bool/Not.h"
#include "Decision.h"

BTT_FSM BTT_FSMCreation::formulaToBTT_FSM(const Formula &formula, bool past) {
    // Only a constant
    if (auto constant = std::dynamic_pointer_cast<Constant>(formula.getExpr())) {
        StateBTT_FSM singleState(constant->getValue(), {}, {});
        return BTT_FSM(formula, {singleState});
    }
    // Get corresponding MT-FSM
    auto mtFsm = MT_FSMCreation::formulaToMT_FSM(formula, past);
    //std::cout << mtFsm.to_string();
    const auto &mtFsmStates = mtFsm.getStates();

    // States of BTT-FSM
    std::vector<StateBTT_FSM> bttStates;

    // Add states true and false
    for (const auto &mtFsmState : mtFsmStates) {
        size_t id = mtFsmState.getId();
        // States false (0) and true (1)
        if (!id or id == 1) {
            bttStates.emplace_back(id);
            continue;
        }
        // Other state
        // Get precedences
        auto precedencesNonTerminal = getAtomicWeight(mtFsmState.getNonTerminal());
        auto precedencesTerminal = getAtomicWeight(mtFsmState.getTerminal());

        // Create BTT for terminal and non-terminal multitransition
        auto bttNonTerminal = findNextNode(mtFsmState.getNonTerminal(), precedencesNonTerminal);
        auto bttTerminal = findNextNode(mtFsmState.getTerminal(), precedencesTerminal);

        // Create new state and add it
        auto newState = StateBTT_FSM(id, bttNonTerminal, bttTerminal);
        bttStates.push_back(newState);
    }

//    auto btt = BTT_FSM(mtFsm.getFormula(), bttStates);
//    std::cout << btt.to_string() << std::endl;
    return BTT_FSM(mtFsm.getFormula(), bttStates);
}

std::map<std::string, size_t> BTT_FSMCreation::getAtomicFrequencies(const MultiTransition &multiTransition) {
    std::map<std::string, size_t> frequencies;
    auto &transitions = multiTransition.getTransitions();
    for (const auto&[formula, state] : transitions) {
        // Formula of transition
        auto atomics = Utils::getAtomics(formula);
        for (const auto &atomic : atomics) {
            // Adds key if it is not yet in map
            frequencies[atomic]++;
        }
    }
    return frequencies;
}

// TODO use Predicates.h for costs
std::multimap<double, std::shared_ptr<Atomic>>
BTT_FSMCreation::getAtomicWeight(const MultiTransition &multiTransition) {
    std::map<std::shared_ptr<Atomic>, double> precedences;
    auto numberOfTransitions = multiTransition.getTransitions().size();
    auto frequencies = getAtomicFrequencies(multiTransition);
    for (const auto&[atomicString, freq] : frequencies) {
        auto atomic = std::make_shared<Atomic>(atomicString);
        precedences[atomic] = 1/(double(freq) / numberOfTransitions);
    }
    return createWeightMultimap(precedences);
}

std::shared_ptr<Expression>
BTT_FSMCreation::replaceAtomicByConstant(const Formula &formula, const std::shared_ptr<Atomic> &atomic, bool constant) {
    auto expression = formula.getExpr();

    // Single atomic
    if (auto atomicExpr = std::dynamic_pointer_cast<Atomic>(expression)) {
        if (*atomicExpr == *atomic) {
            return std::make_shared<Constant>(constant);
        }
        else {
            throw std::runtime_error(
                    "BTT_FSMCreation::replaceAtomicByConstantTrue Single atomic that is not the searched one.");
        }
    }

        // Not atomic
    else if (auto notExpr = std::dynamic_pointer_cast<Not>(expression)) {
        if (*notExpr->getLeft() == *atomic) {
            return std::make_shared<Constant>(!constant);
        }
    }
    // We have an n-ary expression
    auto nary = std::dynamic_pointer_cast<NaryInterface>(expression);

    // If we now don't have an n-ary expression something is really wrong
    if (not nary) {
        throw std::runtime_error("BTT_FSMCreation::replaceAtomicByConstantTrue Expression is not n-ary but should be.");
    }

    // Find atomic and replace it, we definitely don't have fewer than two elements in nary
    auto itr = nary->findExpression(atomic);
    if (itr != nary->end()) {
        nary->eraseExpression(itr);
        nary->addExpression(std::make_shared<Constant>(constant));
        //std::cout << "Found " << atomic->to_string() << std::endl;
    }
        // Atomic could be negated
    else if (auto itrNot = nary->findExpression(std::make_shared<Not>(atomic)); itrNot != nary->end()) {
        nary->eraseExpression(itrNot);
        nary->addExpression(std::make_shared<Constant>(!constant));
        //std::cout << "Found !" << atomic->to_string() << std::endl;

    }

    // Rewrite to reduce if possible
    Formula newFormula(nary);
    BasicRewriteVisitor br;
    br.rewrite(newFormula);
//    std::cout << "Result of " << atomic->to_string() << " replaced with " << constant << " in " << formula.to_string()
//              << ": " << newFormula.to_string() << std::endl;
    return newFormula.getExpr();
}

std::multimap<double, std::shared_ptr<Atomic>>
BTT_FSMCreation::createWeightMultimap(const std::map<std::shared_ptr<Atomic>, double> &weights) {
    std::vector<std::shared_ptr<Atomic>> atomics;
    // Is now ordered by weights
    return flip_map(weights);
}


MultiTransition
BTT_FSMCreation::eraseAtomicFromFormula(const MultiTransition &multiTransition, const std::shared_ptr<Atomic> &atomic) {

    std::map<Formula, size_t> newTransitions;
    // To search for negated atomic
    auto notAtomic = std::make_shared<Not>(atomic);
    BasicRewriteVisitor br;
    for (const auto&[formula, state] : multiTransition.getTransitions()) {
        auto formulaCopy = formula.deepCopy();
        // Erase atomic from formulas
        // Check if only atomic
        if (auto atomicExpr = std::dynamic_pointer_cast<Atomic>(formulaCopy.getExpr())) {
            // Only searched atomic is left -> nothing to do
            if (not(*atomic == *atomicExpr)) {
                Formula newFormula(atomicExpr);
                newTransitions.emplace(newFormula, state);
            }
        }
            // Atomic could be negated
        else if (auto notExpr = std::dynamic_pointer_cast<Not>(formulaCopy.getExpr())) {
            if (not(*notAtomic == *notExpr)) {
                Formula newFormula(notExpr);
                newTransitions.emplace(newFormula, state);
            }
        }
            // Otherwise we have an n-ary
        else if (auto nary = std::dynamic_pointer_cast<NaryInterface>(formulaCopy.getExpr())) {
            nary->eraseExpression(atomic);
            nary->eraseExpression(notAtomic);
            Formula newFormula(nary);
            br.rewrite(newFormula);
            newTransitions.emplace(newFormula, state);
        }
        else {
            throw std::runtime_error(
                    "BTT_FSMCreation::eraseAtomicFromFormula() Formula is neither Atomic, Not, or Nary.");
        }
    }
    return MultiTransition(newTransitions);
}

MultiTransition
BTT_FSMCreation::replaceAtomicInMultiTransition(const MultiTransition &multiTransition,
                                                const std::shared_ptr<Atomic> &atomic, bool constant) {

    std::map<Formula, size_t> newTransitions;
    for (const auto&[formula, state] : multiTransition.getTransitions()) {
        auto newFormula = formula.deepCopy();
        replaceAtomicByConstant(newFormula, atomic, constant);
        newTransitions.emplace(newFormula, state);
    }
    return MultiTransition(newTransitions);
}

std::shared_ptr<Node> BTT_FSMCreation::findNextNode(const MultiTransition &multiTransition,
                                                    std::multimap<double, std::shared_ptr<Atomic>> &weights) {
    // Constant
    if (multiTransition.getTransitions().size() == 1) {
        if (auto constantExpr = std::dynamic_pointer_cast<Constant>(
                (multiTransition.getTransitions().begin()->first.getExpr()))) {
            size_t id = multiTransition.getTransitions().at(multiTransition.getTransitions().begin()->first);
            auto state = std::make_shared<StateBTT_FSM>(id);
            return std::make_shared<Decision>(state, state, constantExpr);
        }
        throw std::runtime_error("BTT_FSMCreation::findNextNode() Multitransition has size 1 and it's not a Constant.");
    }

    // Check all atomics
    for (auto itrPrecedences = weights.begin(); itrPrecedences != weights.end(); ++itrPrecedences) {
        const auto &[precedence, atomic] = *itrPrecedences;
        // In all formulas in multiTransition
        for (const auto&[formula, nextState] : multiTransition.getTransitions()) {
            if (formula.containsAtomic(atomic)) {
                for (bool constant : {true, false}) {
                    //std::cout << "Current atomic: " << atomic->to_string() << " evaluated as " << constant << " on "
                    // << formula.to_string() << std::endl;
                    auto formulaCopy = formula.deepCopy();
                    auto resExpr = replaceAtomicByConstant(formulaCopy, atomic, constant);
//                    std::cout << "Replacing " << atomic->to_string() << " with " << constant << " in " << formulaCopy.to_string() << " is "
//                              << resExpr->to_string() << std::endl;
                    // Check if replacing this atomic resolves the formula to true
                    if (resExpr->isConstTrue()) {
                        // Last atomic = base case
                        if (weights.size() == 1) {
                            auto left = std::make_shared<StateBTT_FSM>(nextState);

                            std::map<std::string,LazyBool> eventMap;

                            eventMap.emplace(atomic->to_string(), LazyBool(not constant));
                            auto right = std::make_shared<StateBTT_FSM>(multiTransition.evaluate(eventMap));
                            // Get left an right in order
                            if (constant) {
                                return std::make_shared<Decision>(left, right, atomic);
                            }
                            return std::make_shared<Decision>(right, left, atomic);
                        }
                        else {
                            // Replace atomic with constant in all formulas by building new multiTransition
                            auto newMultitransition = eraseAtomicFromFormula(multiTransition, atomic);
                            //std::cout << "MT after removing " << atomic->to_string() << "\n" << newMultitransition.to_string() << std::endl;
                            // Copy atomic since we erase it in the next step
                            auto atomicCopy = std::make_shared<Atomic>(atomic->to_string());
                            // Erase atomic from weights
                            weights.erase(itrPrecedences);
                            if (constant) {
                                return std::make_shared<Decision>(std::make_shared<StateBTT_FSM>(nextState),
                                                                  findNextNode(newMultitransition, weights),
                                                                  atomicCopy);
                            }
                            else {
                                return std::make_shared<Decision>(findNextNode(newMultitransition, weights),
                                                                  std::make_shared<StateBTT_FSM>(nextState),
                                                                  atomicCopy);
                            }
                        }
                    }
                }
            }
        }
    }

    // No atomic was found that immediately solves the formula
    // Pick the one with the best precedence
    const auto &[_, atomic] = *weights.begin();

    auto newMultitransitionTrue = replaceAtomicInMultiTransition(multiTransition, atomic, true);
    auto newMultitransitionFalse = replaceAtomicInMultiTransition(multiTransition, atomic, false);

    auto atomicCopy = std::make_shared<Atomic>(atomic->to_string());
    weights.erase(weights.begin());

    return std::make_shared<Decision>(findNextNode(newMultitransitionTrue, weights),
                                      findNextNode(newMultitransitionFalse, weights),
                                      atomicCopy);

    throw std::runtime_error(
            "BTT_FSMCreation::findNextNode() Atomics are not in multiTransition or no transition was found that is satisfied by only one atomic.");
}
