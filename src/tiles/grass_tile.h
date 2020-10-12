#ifndef _GRASS_TILE_H
#define _GRASS_TILE_H

#include "tile.h"


class GrassTile : public Tile
{
public:
    GrassTile(
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