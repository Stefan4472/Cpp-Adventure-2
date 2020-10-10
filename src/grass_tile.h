#ifndef _GRASS_TILE_H
#define _GRASS_TILE_H

#include "tile.h"


class GrassTile : public Tile
{
public:
    GrassTile(double worldX, double worldY);
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* gameRenderer);
};

#endif