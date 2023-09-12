#include "PrimeTerm.h"

#include <utility>
#include <sstream>
#include <iostream>

PrimeTerm::PrimeTerm(std::set<size_t> combinations, std::vector<std::string> allocation,
                     bool hasBeenCombined) : combinations(std::move(combinations)), allocation(std::move(allocation)),
                                             hasBeenCombined(hasBeenCombined) {}

const std::set<size_t> &PrimeTerm::getCombinations() const {
    return combinations;
}

const std::vector<std::string> &PrimeTerm::getAllocation() const {
    return allocation;
}

bool PrimeTerm::getHasBeenCombined() const {
    return hasBeenCombined;
}

void PrimeTerm::setHasBeenCombined(bool hasBeenCombined) {
    PrimeTerm::hasBeenCombined = hasBeenCombined;
}


std::set<size_t>::iterator PrimeTerm::eraseMinTerm(std::set<size_t>::iterator minTermItr) {
    return combinations.erase(minTermItr);
}

bool PrimeTerm::eraseMinTerm(size_t minTerm) {
    return combinations.erase(minTerm);
}

const std::string &PrimeTerm::getAlias() const {
    return alias;
}

void PrimeTerm::setAlias(const std::string &alias) {
    this->alias = alias;
}

std::string PrimeTerm::allocationToFormulaString(const std::vector<std::string> &atomics) {
    // Collect all predicates to be combined
    std::vector<std::string> tmp;
    for (size_t i = 0; i < allocation.size(); ++i) {
        if (allocation[i] == "-") {
            continue;
        }
        else if (allocation[i] == "1") {
            tmp.push_back(atomics[i]);
        }
        else {
            tmp.push_back("!" + atomics[i]);
        }
    }

    // Build string
    std::stringstream res;
    for (size_t i = 0; i < tmp.size() - 1; ++i) {
        res << tmp[i] << " & ";
    }
    res << tmp[tmp.size() - 1];
    return res.str();
}

bool operator==(const PrimeTerm &p1, const PrimeTerm &p2) {
    return p1.getCombinations() == p2.getCombinations();
}
