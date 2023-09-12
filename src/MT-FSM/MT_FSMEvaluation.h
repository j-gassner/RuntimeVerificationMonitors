#pragma once


#include "Formula/Formula.h"
#include "Trace/Trace.h"
#include "MT_FSM.h"

namespace MT_FSMEvaluation {
    /**
     * Checks if a trace satisfies a specification by traversing an MT-FSM*.
     * @param mtFsm
     * @param trace
     * @param past True if formula is in PLTLf.
     * @return True if satisfied, false otherwise.
     */
    [[nodiscard]] bool evaluateMT_FSM(const MT_FSM &mtFsm, Trace &trace, bool past);
}



