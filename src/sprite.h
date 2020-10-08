#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>
#include "game_context.h"
#include "sprite_type.h"


class Sprite
{
public:
    Sprite(GameContext* gameContext, SpriteType spriteType);
    Sprite(GameContext* gameContext, SpriteType spriteType, double worldX, double worldY);
    // World coordinates
    double worldX, worldY;
    // Tile coordinates
    int tileX, tileY;
    
    /* Abstract methods */
    // Draw self onto provided surface
    // virtual void draw(SDL_Surface* surface) = 0;

protected:
    GameContext* gameContext;
    SpriteType spriteType;
};

#endif