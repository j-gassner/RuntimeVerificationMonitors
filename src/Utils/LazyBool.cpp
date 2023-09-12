#include "LazyBool.h"

#include <utility>

LazyBool::LazyBool(std::function<bool()> valueFetcher) : valueFetcher(std::move(valueFetcher)) {}

bool LazyBool::get() {
    if (not initialized) {
        value = valueFetcher();
        initialized = true;
    }
    return value;
}

std::string LazyBool::to_string() const {
    if (initialized) {
        return value ? "true" : "false";
    }
    return "Not initialized";
}

std::ostream &operator<<(std::ostream &os, const LazyBool &lazyBool) {
    return os << lazyBool.to_string();
}

LazyBool::LazyBool(bool value) : value(value), initialized(true) {}
