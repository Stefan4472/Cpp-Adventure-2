#ifndef _SAND_TILE_H
#define _SAND_TILE_H

#include "tile.h"

class SandTile : public Tile
{
public:
    SandTile(double worldX, double worldY);
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* gameRenderer);
};

#endif