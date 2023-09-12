#pragma once

#include "Unary.h"
#include "Trace/Event.h"

/**
 * Class for the EventOperator that applies an event to a formula.
 */
class EventOperator : public Unary {
private:
    Event event;

public:
    /**
     * Constructor.
     * @param left Expression event should be applied to.
     * @param event Event.
     */
    explicit EventOperator(const std::shared_ptr<Expression> &left, Event event) : Unary(
            event.to_string(), left), event(std::move(event)) {}

    /**
     * Getter for event.
     * @return The operator's event.
     */
    [[nodiscard]] Event getEvent();

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &eventVis) override;

    [[nodiscard]] std::string to_string() const override;

};




