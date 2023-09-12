#pragma once

/**
 * Parent class for Decision and StateBTT_FSM since we can have both types in a BTT:
 */
class Node {
public:
    /**
     * Dummy to_string(), gets overwritten in child classes Decision and StateBTT_FSM.
     * @return String representation of the Node.
     */
    [[nodiscard]] virtual std::string to_string() const = 0;
};