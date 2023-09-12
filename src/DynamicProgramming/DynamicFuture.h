#pragma once

#include <algorithm>

#include "ExpressionTree/Expression.h"
#include "Formula/Formula.h"
#include "Trace/Trace.h"

/**
 * DynamicFuture Dynamic programming algorithm for formulas in LTLf.
 */
namespace DynamicFuture {

/**
  * Initializes the vector next with truth values holding in the last event of the trace.
  * @param event Last event in trace.
  * @param subformulas Vector of all subformulas of the formula to be verified.
  * @return Vector next initialized.
  */
    [[nodiscard]] std::vector<bool>
    initializeNext(Event &event, const std::vector<std::shared_ptr<Expression>> &subformulas);

    /**
     * Updates the vector now using vector next.
     * @param event Currently viewed event.
     * @param subformulas Vector of all subformulas of the formula to be verified.
     * @param next Vector from previous event.
     * @return Updated vector now.
     */
    [[nodiscard]] std::vector<bool>
    updateNow(Event &event, const std::vector<std::shared_ptr<Expression>> &subformulas,
              const std::vector<bool> &next);

    /**
     * Checks if a trace satisfies a formula by traversing it backwards.
     * @param formula LTLf formula to be checked.
     * @param trace Event trace.
     * @return True if formula satisfied, false otherwise.
     */
    [[nodiscard]] bool checkTraceDynamically(const Formula &formula, Trace &trace);

}



