#include "util.h"

namespace util
{

std::pair<int, int> calcTileChange(
    int startTileX,
    int startTileY,
    Direction direction,
    int numTilesChange
) {
    switch (direction)
    {
        case Direction::UP:
        {
            return std::make_pair(
                startTileX,
                startTileY - numTilesChange
            );
        }
        case Direction::DOWN:
        {
            return std::make_pair(
                startTileX,
                startTileY + numTilesChange
            );
        }
        case Direction::LEFT:
        {
            return std::make_pair(
                startTileX - numTilesChange,
                startTileY
            );
        }
        case Direction::RIGHT:
        {
            return std::make_pair(
                startTileX + numTilesChange,
                startTileY
            );
        }
        case Direction::NONE:
        {
            return std::make_pair(
                startTileX,
                startTileY
            );
        }
        default:
        {
            throw std::runtime_error(
                "Unhandled case: Programmer error"
            );
        }
    }
}

Direction invertDirection(Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
        {
            return Direction::DOWN;
        }
        case Direction::DOWN:
        {
            return Direction::UP;
        }
        case Direction::LEFT:
        {
            return Direction::RIGHT;
        }
        case Direction::RIGHT:
        {
            return Direction::LEFT;
        }
        default:
        {
            throw std::runtime_error(
                "The specified Direction cannot be inverted"
            );
        }
    }
}
}