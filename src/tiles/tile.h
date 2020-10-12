#ifndef _TILE_H
#define _TILE_H

#include "tile_type.h"
#include "update_context.h"
#include "game_renderer.h"
#include "sprite.h"


class Tile
{
public:
    Tile(TileType tileType, double worldX, double worldY);
    TileType getTileType();
    
    virtual void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    );
    virtual void update(UpdateContext* updateContext) = 0;
    virtual void draw(GameRenderer* gameRenderer) = 0;

protected:
    TileType tileType;
    double worldX, worldY;
};

#endif