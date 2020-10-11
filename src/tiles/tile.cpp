#include "tile.h"

Tile::Tile(TileType tileType, double worldX, double worldY)
{
    this->tileType = tileType;
    this->worldX = worldX;
    this->worldY = worldY;
}

TileType Tile::getTileType()
{
    return tileType;
}

void Tile::respondToInteract(Sprite* owner, Item* withItem)
{
    std::cout << "Tile responding" << std::endl;
}
