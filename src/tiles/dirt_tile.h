#ifndef _DIRT_TILE_H
#define _DIRT_TILE_H

#include "tile.h"

class DirtTile : public Tile
{
public:
    DirtTile(
        GameContext* gameContext, 
        SDL_Rect worldCoords
    );

    void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    );

    void update(UpdateContext& updateContext);
    
    void draw(GameRenderer* gameRenderer);
};

#endif