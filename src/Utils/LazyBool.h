#pragma once

#include <functional>
#include <ostream>

/**
 * Boolean whose value is only initialized when accessed.
 */
class LazyBool {

private:
    bool value{false};
    bool initialized{false};
    std::function<bool()> valueFetcher{};

public:

    LazyBool() : initialized(true) {};

    /**
     * Initialize non-lazy.
     * @param value
     */
    explicit LazyBool(bool value);

    /**
     * Constructor with functions.
     * @param valueFetcher
     */
    explicit LazyBool(std::function<bool()> valueFetcher);

    /**
     * Implicit cast to bool that fetches the value if necessary.
     * @return
     */
    operator bool() {
        return get();
    }

    /**
     * Fetches the value.
     * @return value
     */
    bool get();

    /**
     * Const to_string that indicates the value or not-initialized.
     * @return value
     */
    [[nodiscard]] std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const LazyBool &aBool);
};



