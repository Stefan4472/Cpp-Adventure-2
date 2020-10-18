#ifndef _SPRITE_FACTORY_H
#define _ACTOR_FACTORY_H

#include <memory>
#include "sprite_type.h"
#include "player_actor.h"
#include "npc_actor.h"

// Creates and returns a new Actor for the specified SpriteType.
class ActorFactory
{
public:
    static std::shared_ptr<Actor> createActor(
        GameContext* gameContext,
        SpriteType spriteType,
        int spriteId,
        SDL_Rect worldCoords
    );
};

#endif