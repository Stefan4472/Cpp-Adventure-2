#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>
#include <memory>
#include "game_context.h"
#include "update_context.h"
#include "game_renderer.h"
#include "sprite_type.h"


class Sprite
{
public:
    Sprite(
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType
    );
    Sprite(
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType, 
        double worldX, 
        double worldY
    );
    
    // TODO: DIFFERENTIATE BETWEEN WORLD COORDINATES AND DRAW COORDINATES
    // World coordinates
    double worldX, worldY;
    // Tile coordinates
    int tileX, tileY;
    
    /* Abstract methods */
    // Update
    virtual void update(UpdateContext* updateContext) = 0;
    // Draw self onto provided renderer
    virtual void draw(GameRenderer* renderer) = 0;

protected:
    std::shared_ptr<GameContext> gameContext;
    SpriteType spriteType;
};

#endif