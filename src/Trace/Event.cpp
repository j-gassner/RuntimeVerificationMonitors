#include "Event.h"

bool Event::getValue(const std::string &atomic) {
    return eventMap.at(atomic).get();
}

std::map<std::string, LazyBool> Event::getEventMap() const {
    return this->eventMap;
}

std::map<std::string, LazyBool> &Event::getEventMapRef() {
    return this->eventMap;
}

bool Event::getValue(const Atomic &atomic) {
    return getValue(atomic.to_string());
}

bool Event::isTerminal() const {
    return terminal;
}

void Event::setEventMap(const std::map<std::string, LazyBool> &eventMap) {
    Event::eventMap = eventMap;
}

void Event::setTerminal(bool terminal) {
    Event::terminal = terminal;
}

std::string Event::to_string() const {
    std::stringstream res;
    res << "{";
    for (auto &[key, value] : eventMap) {
        res << key << ": " << value << "; ";
    }
    res << terminal << "}";
    return res.str();
}
