#include <algorithm>
#include <iostream>
#include <cmath>
#include "Rewriting/BasicRewriteVisitor.h"
#include "QMC.h"
#include "Parser/Parser.h"
#include "Utils/Utils.h"
#include "Trace/EventGenerator.h"
#include "ExpressionTree/Atomic/Constant.h"
#include "ExpressionTree/Unary/Bool/Not.h"
#include "ExpressionTree/Nary/Bool/And.h"
#include "ExpressionTree/Nary/Bool/Or.h"
#include "ExpressionTree/Nary/Bool/Xor.h"
#include "QMCTable.h"


std::vector<std::string>
QMC::combineStringVectors(const std::vector<std::string> &v1, const std::vector<std::string> &v2, size_t index) {

    // Combine vectors
    std::vector<std::string> ret(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        ret[i] = i == index ? "-" : v1[i];
    }

    return ret;

}

std::vector<std::string> QMC::booltoStringVector(const std::vector<bool> &boolVec) {
    std::vector<std::string> stringVec;
    stringVec.reserve(boolVec.size());
    for (auto item : boolVec) {
        stringVec.emplace_back(item ? "1" : "0");
    }
    return stringVec;
}

// -1 if cannot be combined, index otherwise
int QMC::canBeCombined(const std::vector<std::string> &vec1, const std::vector<std::string> &vec2) {
    // Only combine if they differ by exactly one digit
    size_t diff = 0;
    size_t index;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
            ++diff;
            index = i;
        }
    }
    if (diff == 1) {
        return index;
    }
    return -1;
}

Formula QMC::minimize(Formula &formula) {
    if (std::dynamic_pointer_cast<NaryInterface>(formula.getExpr())) {
        if (std::dynamic_pointer_cast<And>(formula.getExpr())) {
            formula.setExpr(distributivityExpand<And, Or>(formula.getExpr()));
        }
        else if (std::dynamic_pointer_cast<Or>(formula.getExpr())) {
            formula.setExpr(distributivityExpand<Or, And>(formula.getExpr()));
        }
    }
    BasicRewriteVisitor basicRewriteVisitor;
    basicRewriteVisitor.rewrite(formula);

    return formula;
}

std::string
QMC::nameToAtomics(const std::string &name, const std::map<std::string, std::vector<std::string>> &primeTermsRelevant,
                   const std::set<std::string> &atomics) {
    std::stringstream ret;
    const auto &assignment = primeTermsRelevant.at(name);
    size_t i = 0;
    for (const auto &atomic : atomics) {
        if (assignment[i] == "1") {
            if (ret.tellp() != 0) {
                ret << "&";
            }
            ret << atomic;
        }
        else if (assignment[i] == "0") {
            if (ret.tellp() != 0) {
                ret << "&";
            }
            ret << "!" << atomic;
        }
        ++i;
    }
    return ret.str();
}

Formula QMC::reduceBoolFormula(const Formula &formula) {
    if (not std::dynamic_pointer_cast<And>(formula.getExpr()) and
        not std::dynamic_pointer_cast<Or>(formula.getExpr())) {
        return formula;
    }
    size_t numberOfAtomics = Utils::getNumberOfAtomics(formula.getExpr());
    EventGenerator gen(numberOfAtomics);
    QMCTable qmcTable({});

    // Truth table for all combinations, only add minTerms (evaluate to 1)
    size_t index = 0;
    for (auto event = gen.getEventVector(); gen.hasNext(); event = gen.getNext()) {
        auto currentEvent = Utils::boolVectorToEvent(Utils::getAtomics(formula.getExpr()), event, false);
        auto truthValue = Utils::evaluateBooleanExpression(formula.getExpr(), currentEvent.getEventMapRef());
        if (truthValue) {
            // Add to table
            qmcTable.addPrimeTerm(PrimeTerm({index}, booltoStringVector(event), false));
        }
        ++index;
    }

    // Everything evaluates to false -> return false
    if (qmcTable.getPrimeTerms().empty()) {
        return Formula(std::make_shared<Constant>(false));
    }
    // If everything evaluates to true return true
    if (qmcTable.getPrimeTerms().size() == 1ul << numberOfAtomics) {
        return Formula(std::make_shared<Constant>(true));
    }

    // Find essential primeTerms
    qmcTable.combinePrimeTerms();

    // Apply Petrick's method
    auto atomics = Utils::getAtomics(formula.getExpr());
    auto atomicsVector = std::vector<std::string>(atomics.begin(), atomics.end());
    auto reducedFormula = qmcTable.petrick(atomicsVector);
    return reducedFormula;
}



