#pragma once

#include <algorithm>
#include "ExpressionTree/Expression.h"
#include "Formula/Formula.h"
#include "Trace/Trace.h"

/**
 * DynamicPast Dynamic programming algorithm for formulas in pLTLf.
 */

namespace DynamicPast {

/**
  * Initializes the vector pre with truth values holding in the first event of the trace.
  * @param event First event in trace.
  * @param subformulas Vector of all subformulas of the formula to be verified.
  * @return Vector pre initialized.
  */
    [[nodiscard]] std::vector<bool>
    initializePre(Event &event, const std::vector<std::shared_ptr<Expression>> &subformulas);

    /**
     * Updates the vector now using vector pre.
     * @param event Currently viewed event.
     * @param subformulas Vector of all subformulas of the formula to be verified.
     * @param pre Vector from previous event.
     * @return Updated vector now.
     */
    [[nodiscard]] std::vector<bool>
    updateNow(Event &event, const std::vector<std::shared_ptr<Expression>> &subformulas,
              const std::vector<bool> &pre);

    /**
     * Checks if a trace satisfies a formula by traversing it forwards.
     * @param formula pLTLf formula to be checked.
     * @param trace Event trace.
     * @return True if formula satisfied, false otherwise.
     */
    [[nodiscard]] bool checkTraceDynamically(const Formula &formula, Trace &trace);

};




