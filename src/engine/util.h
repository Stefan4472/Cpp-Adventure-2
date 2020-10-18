#ifndef _ENGINE_UTIL_H
#define _ENGINE_UTIL_H

#include <utility>
#include <stdexcept>
#include "direction.h"

namespace util
{

// Calculate (`startTileX`, `startTileY`) + `numTilesChange` in `direction`
std::pair<int, int> calcTileChange(
    int startTileX,
    int startTileY,
    Direction direction,
    int numTilesChange = 1
);

// Return the "inverse" / opposite of the specified Direction
Direction invertDirection(Direction direction);
}
#endif