#pragma once


#include <map>
#include <sstream>
#include "Utils/LazyBool.h"
#include "ExpressionTree/Atomic/Atomic.h"

/**
 * Event of a trace.
 */
class Event {
private:
    std::map<std::string, LazyBool> eventMap;
    bool terminal;

public:
    /**
     * Constructor.
     * @param event Map from predicates to LazyBool.
     * @param terminal True if event is terminal, false other wise.
     */
    explicit Event(std::map<std::string, LazyBool> &event, bool terminal) : eventMap(event), terminal(terminal) {}

    /**
     * Getter for the truth value of an atomic.
     * @param atomic
     * @return Truth value of the atomic.
     */
    [[nodiscard]] bool getValue(const std::string &atomic);

    /**
     * Getter for event map.
     * @return eventMap.
     */
    [[nodiscard]] std::map<std::string, LazyBool> getEventMap() const;

    /**
     * Getter for event map as reference.
     * @return Reference to event map.
     */
    [[nodiscard]] std::map<std::string, LazyBool> &getEventMapRef();

    /**
     * Getter for the truth value of an atomic.
     * @param atomic
     * @return Truth value of the atomic.
     */
    [[nodiscard]] bool getValue(const Atomic &atomic);

    /**
     *
     * @return True if terminal, false otherwise.
     */
    [[nodiscard]] bool isTerminal() const;

    /**
     * Setter for eventMap.
     * @param eventMap
     */
    void setEventMap(const std::map<std::string, LazyBool> &eventMap);

    /**
     * Setter for terminal attribute.
     * @param terminal
     */
    void setTerminal(bool terminal);

    [[nodiscard]] std::string to_string() const;
};



