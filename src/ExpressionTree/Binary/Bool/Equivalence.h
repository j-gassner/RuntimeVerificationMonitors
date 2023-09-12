#pragma once


#include "ExpressionTree/Binary/Binary.h"

/**
 * Class representing an Equivalence.
 */
class Equivalence : public Binary {

public:
    /**
     * Constructor.
     * @param left Left expression of the equivalence.
     * @param right Right expression of the equivalence.
     */
    Equivalence(const std::shared_ptr<Expression> &left, const std::shared_ptr<Expression> &right
    ) : Binary(
            equivalenceSymbol, left, right) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;

};




