#ifndef _TILE_H
#define _TILE_H

#include "tile_type.h"
#include "game_context.h"
#include "update_context.h"
#include "game_renderer.h"
#include "sprite.h"


// Minimal Tile abstract parent class.
// Keeping things barebones until we determine the exact features
// we want every `Tile` to have.
class Tile
{
public:
    Tile(
        GameContext* gameContext, 
        TileType tileType, 
        SDL_Rect worldCoords
    );

    TileType getTileType();
    
    virtual void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    ) = 0;

    virtual void update(UpdateContext& updateContext) = 0;

    virtual void draw(GameRenderer* gameRenderer) = 0;

protected:
    GameContext* gameContext;
    TileType tileType;
    SDL_Rect worldCoords;
};

#endif