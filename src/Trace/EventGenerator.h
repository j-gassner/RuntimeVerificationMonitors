#pragma once


#include <vector>

/**
 * Class to generate events for a number of predicates.
 * E.g. for two predicates a and b, the events (true, true), (true, false), (false, true), (false, false) are generated.
 */
class EventGenerator {
private:
    std::vector<bool> event;
    size_t numberOfTrue;
public:
    /**
     * Constructor.
     * @param length
     */
    explicit EventGenerator(size_t length);

    /**
     * Getter for event.
     * @return
     */
    [[nodiscard]] const std::vector<bool> &getEventVector() const;

    /**
     * Next event.
     * @return
     */
    [[nodiscard]] const std::vector<bool> &getNext();

    /**
     *
     * @return True if there still is a next event.
     */
    [[nodiscard]] bool hasNext();

};



