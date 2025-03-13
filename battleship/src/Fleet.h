#pragma once

#include <vector>
#include "Boat.h"

/**
 * Utility container structure
 */
struct Fleet
{
    std::vector<Boat> boats;

    Fleet ();

    bool IsDestroyed() const;

};
