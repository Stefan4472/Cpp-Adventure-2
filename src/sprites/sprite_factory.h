#ifndef _SPRITE_FACTORY_H
#define _SPRITE_FACTORY_H

#include <memory>
#include "sprite_type.h"
#include "player_sprite.h"
#include "friendly_sprite.h"

// Creates and returns a new Sprite of the specified SpriteType.
class SpriteFactory
{
public:
    static std::shared_ptr<Sprite> createSprite(
        GameContext* gameContext,
        SpriteType spriteType,
        SDL_Rect worldCoords
    );
};

#endif