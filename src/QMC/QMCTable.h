#pragma once

#include <vector>
#include <Formula/Formula.h>
#include "PrimeTerm.h"

/**
 * Class representing the table for the QMC.
 */
class QMCTable {
private:
    std::vector<PrimeTerm> primeTerms;

public:
    /**
     * Constructor.
     * @param primeTerms
     */
    explicit QMCTable(std::vector<PrimeTerm> primeTerms);

    /**
     * Erases prime terms that were combined.
     */
    void eraseCombinedPrimeTerms();

    /**
     * Getter for primeTerms.
     * @return primeTerms.
     */
    [[nodiscard]] const std::vector<PrimeTerm> &getPrimeTerms() const;

    /**
     * Adds a primeTerm.
     * @param primeTerm
     */
    void addPrimeTerm(const PrimeTerm &primeTerm);

    /**
     * Combines prime terms if possible.
     */
    void combinePrimeTerms();

    /**
     * Checks for column dominance.
     * @return True if there are dominant columns.
     */
    bool columnDominance();

    /**
     * Checks for row dominance.
     * @return True if there are dominant rows.
     */
    bool rowDominance();

    /**
     * Checks if a minterm is unique.
     * @param minTerm
     * @param primeTermId
     * @return True if minTerm is unique.
     */
    bool isUnique(size_t minTerm, size_t primeTermId);

    /**
     * Erases a minterm.
     * @param minTerm
     * @param primeTermId
     * @return True if minTerm was erased.
     */
    bool eraseMinTerm(size_t minTerm, size_t primeTermId);

    /**
     * Erases all empty primeterms.
     */
    void eraseEmptyPrimeTerms();

    /**
     * Builds a product of sums.
     * @return
     */
    std::string buildPOS();

    /**
     * Applies Petrick's method to find reduction.
     * @param atomics
     * @return
     */
    Formula petrick(const std::vector<std::string> &atomics);

    /**
     * Finds primterm mapped to alias.
     * @param alias
     * @return primTerm mapped to alias.
     */
    PrimeTerm findPrimeTerm(const std::string &alias);
};



