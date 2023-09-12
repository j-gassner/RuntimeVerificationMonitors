#pragma once


#include "ExpressionTree/Binary/Binary.h"

/**
 * Class representing a Release.
 */
class Release : public Binary {
public:

    /**
     * Constructor.
     * @param left Left expression of the release.
     * @param right Right expression of the release.
     */
    Release(const std::shared_ptr<Expression> &left, const std::shared_ptr<Expression> &right
    ) : Binary(releaseSymbol, left, right) {}

    [[nodiscard]] std::shared_ptr<Expression> clone() override;

    [[nodiscard]] std::shared_ptr<Expression> accept(ExpressionVisitor &visitor, Event &event) override;

};



