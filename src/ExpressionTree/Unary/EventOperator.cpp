#include "EventOperator.h"

std::shared_ptr<Expression> EventOperator::clone() {
    return std::make_shared<EventOperator>(*this);
}

std::shared_ptr<Expression> EventOperator::accept(ExpressionVisitor &visitor, Event &eventVis) {
    return visitor.visitEventOperator(*this, eventVis);
}

Event EventOperator::getEvent() {
    return event;
}

std::string EventOperator::to_string() const {
    return "E(" + getLeft()->to_string() + event.to_string() + ")";
}
