#include "tile.h"

Tile::Tile(
        GameContext* gameContext, 
        TileType tileType, 
        SDL_Rect worldCoords
) {
    this->gameContext = gameContext;
    this->tileType = tileType;
    this->worldCoords = worldCoords;
}

TileType Tile::getTileType()
{
    return tileType;
}