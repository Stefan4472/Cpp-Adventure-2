#ifndef _DIRT_TILE_H
#define _DIRT_TILE_H

#include "tile.h"

class DirtTile : public Tile
{
public:
    DirtTile(double worldX, double worldY);
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* gameRenderer);
};

#endif