#pragma once

#include <set>
#include <vector>
#include <string>

/**
 * Class representing a prime term in the Quine-McCluskey algorithm.
 */
class PrimeTerm {
private:
    std::set<size_t> combinations;
    std::vector<std::string> allocation;
    bool hasBeenCombined;
    std::string alias;

public:
    /**
     * Constrcutor.
     * @param combinations
     * @param allocation
     * @param hasBeenCombined
     */
    PrimeTerm(std::set<size_t> combinations, std::vector<std::string> allocation, bool hasBeenCombined);

    /**
     * Sets hasBeenCombined flag.
     * @param hasBeenCombined
     */
    void setHasBeenCombined(bool hasBeenCombined);

    /**
     * Erases a minterm.
     * @param minTermItr
     * @return
     */
    std::set<size_t>::iterator eraseMinTerm(std::set<size_t>::iterator minTermItr);

    /**
     * Erases a minterm.
     * @param minTerm
     * @return True if minterm was erased, false otherwise.
     */
    bool eraseMinTerm(size_t minTerm);

    /**
     * Sets an alias for a predicate.
     * @param alias
     */
    void setAlias(const std::string &alias);

    /**
     * Gets all possible combinations of minterms.
     * @return All possible combinations of minterms.
     */
    [[nodiscard]] const std::set<size_t> &getCombinations() const;

    /**
     * Getter for allocation.
     * @return allocation.
     */
    [[nodiscard]] const std::vector<std::string> &getAllocation() const;

    /**
     * Getter for hasBeenCombined.
     * @return hasBeenCombined.
     */
    [[nodiscard]] bool getHasBeenCombined() const;

    /**
     * Getter for alias.
     * @return alias.
     */
    [[nodiscard]] const std::string &getAlias() const;

    /**
     * Transforms an allocation into a string.
     * @param atomics
     * @return string of allocations.
     */
    [[nodiscard]] std::string allocationToFormulaString(const std::vector<std::string> &atomics);

    /**
     * Iterator to begin of combinations.
     * @return Iterator to begin of combinations.
     */
    auto begin() {
        return combinations.begin();
    }

    /**
     * Iterator to end of combinations.
     * @return Iterator to end of combinations.
     */
    auto end() {
        return combinations.end();
    }

};

bool operator==(const PrimeTerm &p1, const PrimeTerm &p2);




