#ifndef _STONE_TILE_H
#define _STONE_TILE_H

#include "tile.h"

class StoneTile : public Tile
{
public:
    StoneTile(double worldX, double worldY);
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* gameRenderer);
};

#endif