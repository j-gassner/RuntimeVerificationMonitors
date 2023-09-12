#include "QMCTable.h"
#include "QMC.h"
#include "Parser/Parser.h"

#include <utility>
#include <algorithm>
#include <Utils/Utils.h>

QMCTable::QMCTable(std::vector<PrimeTerm> primeTerms) : primeTerms(std::move(primeTerms)) {}

const std::vector<PrimeTerm> &QMCTable::getPrimeTerms() const {
    return primeTerms;
}

void QMCTable::eraseCombinedPrimeTerms() {
    for (auto itr = primeTerms.begin(); itr != primeTerms.end();) {
        if ((*itr).getHasBeenCombined()) {
            primeTerms.erase(itr);
        }
        else {
            ++itr;
        }
    }
}

void QMCTable::addPrimeTerm(const PrimeTerm &primeTerm) {
    primeTerms.push_back(primeTerm);

}

void QMCTable::combinePrimeTerms() {
    if (primeTerms.empty()) {
        return;
    }

    std::vector<PrimeTerm> primeTermsTemp;
    std::vector<PrimeTerm> primeTermsNew = primeTerms;
    bool changed = true;
    while (changed) {
        changed = false;
        primeTermsTemp = primeTermsNew;
        primeTermsNew.clear();
        for (auto itrOuter = primeTermsTemp.begin(); itrOuter != --primeTermsTemp.end(); ++itrOuter) {
            for (auto itrInner = itrOuter; itrInner != primeTermsTemp.end(); ++itrInner) {
                if (itrInner == itrOuter) {
                    continue;
                }
                auto combineAt = QMC::canBeCombined(itrOuter->getAllocation(), itrInner->getAllocation());
                if (combineAt != -1) {
                    changed = true;
                    auto outerSet = itrOuter->getCombinations();
                    auto innerSet = itrInner->getCombinations();
                    outerSet.merge(innerSet);
                    PrimeTerm newCombination(outerSet, QMC::combineStringVectors(itrOuter->getAllocation(),
                                                                                 itrInner->getAllocation(), combineAt),
                                             false);

                    // Find combined elements in primeTerms (duplicates should be marked, too, but not added)
                    auto itrIndexFirst = std::find(primeTerms.begin(), primeTerms.end(), *itrOuter);
                    auto itrIndexSecond = std::find(primeTerms.begin(), primeTerms.end(), *itrInner);
                    auto indexFirst = std::distance(primeTerms.begin(), itrIndexFirst);
                    auto indexSecond = std::distance(primeTerms.begin(), itrIndexSecond);

                    // Indicate minterms that have been combined
                    primeTerms[indexFirst].setHasBeenCombined(true);
                    primeTerms[indexSecond].setHasBeenCombined(true);

                    // Avoid duplicates
                    if (std::find(primeTerms.begin(), primeTerms.end(), newCombination) == primeTerms.end()) {
                        primeTermsNew.push_back(newCombination);
                        primeTerms.push_back(newCombination);

                    }
                }
            }
        }
    }
    eraseCombinedPrimeTerms();
    changed = true;

    // Apply column and row dominance as long as possible
    while (changed) {
        changed = columnDominance() or rowDominance();
    }

}

bool QMCTable::columnDominance() {
    bool changed = false;
    for (size_t currentPrimeTermId = 0; currentPrimeTermId < primeTerms.size(); ++currentPrimeTermId) {

        // Check if prime term contains at least one unique minTerm
        bool primeTermContainsUnique = false;
        for (auto minTerm : primeTerms[currentPrimeTermId]) {
            if (isUnique(minTerm, currentPrimeTermId)) {
                primeTermContainsUnique = true;
                break;
            }
        }

        // If something was found trigger erase procedure
        if (primeTermContainsUnique) {
            // For every minTerm ...
            for (auto minTermItr = primeTerms[currentPrimeTermId].begin();
                 minTermItr != primeTerms[currentPrimeTermId].end();) {
                bool erased = false;
                // ... erase it from every other prime term and check if anything was erased ...
                if (eraseMinTerm(*minTermItr, currentPrimeTermId)) {
                    // ... if yes then also erase it from the current prime term
                    minTermItr = primeTerms[currentPrimeTermId].eraseMinTerm(minTermItr);
                    erased = true;
                    changed = true;
                }
                // Only advance iterator if erase was not called
                if (not erased) {
                    ++minTermItr;
                }
            }
        }
    }
    eraseEmptyPrimeTerms();
    return changed;
}

bool QMCTable::isUnique(size_t minTerm, size_t primeTermId) {
    for (size_t i = 0; i < primeTerms.size(); ++i) {
        if (primeTermId == i) {
            continue;
        }
        if (primeTerms[i].getCombinations().count(minTerm) == 1) {
            return false;
        }
    }
    return true;
}

bool QMCTable::eraseMinTerm(size_t minTerm, size_t primeTermId) {
    bool erased = false;
    for (size_t i = 0; i < primeTerms.size(); ++i) {
        if (primeTermId == i) {
            continue;
        }
        if (primeTerms[i].eraseMinTerm(minTerm)) {
            erased = true;
        }
    }
    return erased;
}

void QMCTable::eraseEmptyPrimeTerms() {
    primeTerms.erase(std::remove_if(primeTerms.begin(), primeTerms.end(),
                                    [](auto primeTerm) { return primeTerm.getCombinations().empty(); }),
                     primeTerms.end());


}

bool QMCTable::rowDominance() {
    bool changed = false;
    for (auto itrOuter = primeTerms.begin(); itrOuter != primeTerms.end();) {
        bool incrItr = true;
        for (auto itrInner = primeTerms.begin(); itrInner != primeTerms.end(); ++itrInner) {
            if (*itrOuter == *itrInner) {
                continue;
            }
            std::set<size_t> tmp;
            std::set_difference(itrOuter->begin(), itrOuter->end(), itrInner->begin(), itrInner->end(),
                                std::insert_iterator(tmp, tmp.begin()));
            // Outer is subset of inner
            if (tmp.empty()) {
                incrItr = false;
                changed = true;
                primeTerms.erase(itrOuter);
                break;
            }
        }
        if (incrItr) {
            ++itrOuter;
        }
    }
    eraseEmptyPrimeTerms();
    return changed;
}

//std::string QMCTable::buildFormulaString(const std::vector<std::string> &atomics) {
//    // Get all andExpr for final orExpr
//    std::vector<std::vector<std::string>> orExpr;
//    for (auto &primeTerm : primeTerms) {
//        std::vector<std::string> tmp;
//        for (size_t j = 0; j < primeTerm.getAllocation().size(); ++j) {
//            if (primeTerm.getAllocation()[j] == "-") {
//                continue;
//            }
//            else if (primeTerm.getAllocation()[j] == "1") {
//                tmp.push_back(atomics[j]);
//            }
//            else {
//                tmp.push_back("!" + atomics[j]);
//            }
//        }
//        orExpr.push_back(tmp);
//        tmp.clear();
//    }
//
//    // Build final formula
//    std::stringstream res;
//    for (size_t i = 0; i < orExpr.size(); ++i) {
//        res << "(";
//        for (size_t j = 0; j < orExpr[i].size(); ++j) {
//            // No extra &
//            if (j != orExpr[i].size() - 1) {
//                res << orExpr[i][j] << " & ";
//            }
//            else {
//                res << orExpr[i][j];
//            }
//        }
//        // No extra |
//        if (i != orExpr.size() - 1) {
//            res << ") | ";
//        }
//        else {
//            res << ")";
//        }
//    }
//
//    return res.str();
//}

std::string QMCTable::buildPOS() {
    // Find prime implicants to be combined
    std::vector<std::string> orExpressions;
    // TODO use iterators
    for (size_t primeTermCurrent = 0; primeTermCurrent < primeTerms.size(); ++primeTermCurrent) {
        bool combined = false;
        for (size_t primeTermOther = 0; primeTermOther < primeTerms.size(); ++primeTermOther) {
            if (primeTermCurrent == primeTermOther) {
                continue;
            }
            // We only need an Or if there is an intersection
            std::set<size_t> intersection;
            std::set_intersection(primeTerms[primeTermCurrent].getCombinations().begin(),
                                  primeTerms[primeTermCurrent].getCombinations().end(),
                                  primeTerms[primeTermOther].getCombinations().begin(),
                                  primeTerms[primeTermOther].getCombinations().end(),
                                  std::inserter(intersection, intersection.begin()));
            if (!intersection.empty()) {
                combined = true;
                orExpressions.push_back(
                        "(" + primeTerms[primeTermCurrent].getAlias() + " | " + primeTerms[primeTermOther].getAlias() +
                        ")");

            }
        }
        if (!combined) {
            // Don't forget the singles
            orExpressions.push_back(primeTerms[primeTermCurrent].getAlias());
        }
    }

    // Build final string
    std::stringstream res;
    for (size_t i = 0; i < orExpressions.size() - 1; ++i) {
        res << orExpressions[i] << " & ";
    }
    res << orExpressions[orExpressions.size() - 1];
    return res.str();
}

Formula QMCTable::petrick(const std::vector<std::string> &atomics) {
    // Give aliases to primeterms for SOP
    char alias = 'a';
    for (auto &primeTerm : primeTerms) {
        primeTerm.setAlias(std::string(1, alias));
        ++alias;
    }

    auto pos = buildPOS();
    auto posFormula = Parser::parse(pos);
    auto sopFormula = QMC::minimize(posFormula);
    auto sopFormulaString = posFormula.to_string();

    // Remove whitespaces
    sopFormulaString.erase(std::remove(sopFormulaString.begin(), sopFormulaString.end(), ' '), sopFormulaString.end());
    auto splitTerms = Utils::splitString(sopFormulaString, "|()");

    // Choose product with fewest terms
    auto shortest = *std::min_element(splitTerms.begin(), splitTerms.end(),
                                      [](const std::string &s1, const std::string &s2) {
                                          return s1.length() < s2.length();
                                      }
    );

    // Reassign primeTerms
    std::stringstream res;
    res << "(";
    for (const auto &c : shortest) {
        if (c == '&') {
            res << ") | (";
        }
        else if (c != ' ' and c != '(' and c != ')') {
            res << findPrimeTerm(std::string(1, c)).allocationToFormulaString(atomics);
        }
        else {
            continue;
        }
    }
    res << ")";
    return Parser::parse(res.str());
}

PrimeTerm QMCTable::findPrimeTerm(const std::string &alias) {
    for (const auto &primeTerm : primeTerms) {
        if (primeTerm.getAlias() == alias) {
            return primeTerm;
        }
    }
    throw std::runtime_error("QMCTable::findPrimeTerm PrimeTerm not found");
}

