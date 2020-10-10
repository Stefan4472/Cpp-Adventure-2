#include "tile.h"

Tile::Tile(TileType tileType, double worldX, double worldY)
{
    this->tileType = tileType;
    this->worldX = worldX;
    this->worldY = worldY;
}