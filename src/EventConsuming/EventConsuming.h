#pragma once


#include <Formula/Formula.h>
#include <Trace/Trace.h>

/**
 * Functions for monitoring a trace using the eventconsuming algorithm.
 */
namespace EventConsuming {
    /**
     * Monitors a formula in LTLf on a trace.
     * @param formula Formula.
     * @param trace Trace.
     * @return Formula changed by the eventconsuming algorithm, should be true or false at the end.
     */
    [[nodiscard]] Formula eventConsumingFuture(const Formula &formula, Trace &trace);

    /**
     * Monitors a formula in pLTL on a trace.
     * @param formula Formula.
     * @param trace Trace.
     * @return Formula changed by the eventconsuming algorithm, should be true or false at the end.
     */
    [[nodiscard]] Formula eventConsumingPast(const Formula &formula, Trace &trace);

    [[nodiscard]] bool eventConsuming(const Formula &formula, Trace &trace, bool past);

};



