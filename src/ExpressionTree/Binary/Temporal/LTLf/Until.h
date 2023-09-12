#pragma once


#include <ExpressionTree/Binary/Binary.h>

/**
 * Class representing an Until.
 */
class Until : public Binary {
public:
    /**
     * Constructor.
     * @param left Left expression of the until.
     * @param right Right expression of the until.
     */
    Until(const std::shared_ptr<Expression> &left, const std::shared_ptr<Expression> &right) : Binary(untilSymbol, left,
                                                                                                      right) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;
};



