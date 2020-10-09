#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>
#include <memory>
#include "game_context.h"
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
    
    // World coordinates
    double worldX, worldY;
    // Tile coordinates
    int tileX, tileY;
    
    /* Abstract methods */
    // Draw self onto provided renderer
    virtual void draw(SDL_Renderer* renderer) = 0;

protected:
    std::shared_ptr<GameContext> gameContext;
    SpriteType spriteType;
};

#endif