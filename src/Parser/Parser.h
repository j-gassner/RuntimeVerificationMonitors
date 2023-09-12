#pragma once


#include <string>
#include "Formula/Formula.h"

/**
 * Parser class to parse and directly build the formula.
 */
class Parser {
public:
    /**
     * Transforms a formula string into a formula object.
     * @param formula Formula string to be parsed.
     * @return Formula object.
     */
    [[nodiscard]] static Formula parse(const std::string &formula);
};



