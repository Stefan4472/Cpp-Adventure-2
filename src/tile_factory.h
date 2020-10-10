#ifndef _TILE_FACTORY_H
#define _TILE_FACTORY_H

#include <memory>
#include "tile_type.h"
#include "tile.h"
#include "grass_tile.h"
#include "sand_tile.h"
#include "dirt_tile.h"
#include "stone_tile.h"

class TileFactory
{
public:
    static std::shared_ptr<Tile> createTile(
        TileType tileType, 
        double worldX, 
        double worldY
    );
};

#endif