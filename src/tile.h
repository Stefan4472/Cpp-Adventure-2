#ifndef _TILE_H
#define _TILE_H

#include "tile_type.h"
#include "update_context.h"
#include "game_renderer.h"

class Tile
{
public:
    Tile(TileType tileType);
    virtual void update(UpdateContext* updateContext) = 0;
    virtual void draw(GameRenderer* gameRenderer) = 0;
private:
    TileType tileType;
};

#endif