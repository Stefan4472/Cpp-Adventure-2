#ifndef _STONE_TILE_H
#define _STONE_TILE_H

#include "tile.h"

class StoneTile : public Tile
{
public:
    StoneTile(
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