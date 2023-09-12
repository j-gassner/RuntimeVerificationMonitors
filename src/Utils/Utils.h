#pragma once

#include <vector>
#include "Formula/Formula.h"
#include "Trace/Trace.h"
#include "MT-FSM/MultiTransition.h"
#include "MT-FSM/MT_FSM.h"

/**
 * Utils Several functions for working with formulas, traces, and events.
 */
namespace Utils {

    /**
     * Computes how a boolean @param expr (containing only n-ary operators and not) evaluates on a given @param eventMap
     *
     * @param expr Expression to be evaluated.
     * @param eventMap Event.
     * @return True if @param expr is true in @param eventMap, false otherwise.
     */
    [[nodiscard]] bool
    evaluateBooleanExpression(const std::shared_ptr<Expression> &expr, std::map<std::string, LazyBool> &eventMap);

    /**
     * Creates a Trace.
     *
     * @param atomics All possible predicates as strings.
     * @param trueAtomics Vector of vectors containing predicates that are true in each event.
     * @return Trace.
     */
    [[nodiscard]] Trace
    createTrace(const std::set<std::string> &atomics, std::vector<std::vector<std::string>> trueAtomics);

    /**
     * Creates a Trace with lazy evaluation of the predicates.
     * @param atomicsAndFunctions
     * @param length
     * @return
     */
    [[nodiscard]] Trace
    createLazyTrace(const std::map<std::string, std::function<bool(int)>> &atomicsAndFunctions,
                    size_t length);

    /**
     * Creates a string set of all predicates in a formula. Wrapper for getAtomics().
     *
     * @param formula Formula.
     * @return string set of all predicates in @param formula.
     */
    [[nodiscard]] std::set<std::string> getAtomics(const Formula &formula);

    /**
     * Creates a string set of all predicates in an expression. Wrapper for getAtomics().
     *
     * @param expr Expression.
     * @return string set of all predicates in @param expr.
     */
    [[nodiscard]] std::set<std::string> getAtomics(const std::shared_ptr<Expression> &expr);

    /**
     * Creates a string set of all predicates in an expression.
     *
     * @param expr Expression.
     * @param atomics Set of all predicates that is built recursively.
     * @return string set of all predicates in @param expr.
     */
    [[nodiscard]] std::set<std::string>
    getAtomics(const std::shared_ptr<Expression> &expr, std::set<std::string> atomics);

    /**
     * Computes the number of predicates is @param expr.
     *
     * @param expr Expression.
     * @return Number of predicates.
     */
    [[nodiscard]] int getNumberOfAtomics(const std::shared_ptr<Expression> &expr);

    /**
    * Creates event mapping from predicates (=names) to values (=bools) and wraps it into a trace of length 1.
     *
     * @param atomics Names of predicates.
     * @param vector Values of predicates.
     * @param terminal Whether or not the event resulting should be marked as terminal.
     * @return Trace containing only the event defined by the input
     */
    [[nodiscard]] Trace
    boolVectorToTrace(const std::set<std::string> &atomics, const std::vector<bool> &vector, bool terminal);

    /**
    * Creates event mapping from predicates (=names) to values (=bools).
     *
     * @param atomics Names of predicates.
     * @param vector Values of predicates.
     * @param terminal Whether or not the event resulting should be marked as terminal.
     * @return Event containing passed event mapping.
     */
    [[nodiscard]] Event
    boolVectorToEvent(const std::set<std::string> &atomics, const std::vector<bool> &vector, bool terminal);

    /**
     * Creates a formula through conjunction of predicates in @param event.
     *
     * @param event Event.
     * @return Formula with conjunction of predicates.
     */
    [[nodiscard]] Formula eventToFormula(Event &event);

    /**
     * Creates a vector with all subformulas in @param formula including the formula itself with a BFS.
     *
     * @param formula Formula.
     * @return Vector of subformulas.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Expression>> subformulasBreadthFirstOrder(const Formula &formula);

    /**
     * Creates a string representation of an iterable container @param arr.
     *
     * @tparam T Container type.
     * @tparam F Type of print function
     * @param arr Iterable container.
     * @param f function to transform the dereferenced iterator to a string.
     * @return String representation of arr.
     */
    template<class T, class F>
    [[nodiscard]] std::string
    iterableToString(const T &arr,
                     F f,
                     const std::pair<std::string, std::string> &delimiter = {"[", "]"},
                     std::string separator = ", ") {
        auto it = std::begin(arr);
        const auto end = std::end(arr);
        if (it == end) {
            return delimiter.first + delimiter.second;
        }
        std::ostringstream strStream;
        strStream << delimiter.first << f(*it);
        for (++it; it != end; ++it) {
            strStream << separator << f(*it);
        }
        strStream << delimiter.second;
        return strStream.str();
    }

    /**
     *
     *
     * @tparam T Container type.
     * @param arr Iterable container.
     * @return String representation of arr.
     */
    template<class T>
    [[nodiscard]] std::string iterableToString(const T &arr) {
        return iterableToString(arr, [](const auto &x) { return x; });
    }

    /**
     * Splits a string by multiple delimiters.
     *
     * @param SearchString.
     * @param Delimiters
     * @return Set of substrings.
    */
    std::vector<std::string> splitString(const std::string &stringOriginal, const std::string &delimiters);
}
