#ifndef _SAND_TILE_H
#define _SAND_TILE_H

#include "tile.h"

class SandTile : public Tile
{
public:
    SandTile(
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