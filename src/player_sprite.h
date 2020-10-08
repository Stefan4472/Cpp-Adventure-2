#ifndef _PLAYER_SPRITE_H
#define _PLAYER_SPRITE_H

#include "sprite.h"


class PlayerSprite : public Sprite 
{
public:
    PlayerSprite(GameContext* gameContext, SpriteType spriteType, double worldX, double worldY);
    
    void draw(SDL_Surface* surface);

private:
    SDL_Surface* spriteImage;
};

#endif