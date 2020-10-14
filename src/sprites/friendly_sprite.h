#ifndef _FRIENDLY_SPRITE_H
#define _FRIENDLY_SPRITE_H

#include <SDL2/SDL.h>
#include "sprite.h"


class FriendlySprite : public Sprite
{
public:
    FriendlySprite(
        std::shared_ptr<GameContext> gameContext, 
        SDL_Rect& baseTile
    );
    
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* renderer);
};

#endif