#ifndef _NPC_ACTOR_H
#define _NPC_ACTOR_H

#include "actor.h"
#include "input_event.h"
#include "input_handler.h"
#include "inventory.h"


class NPCActor : public Actor
{
public:
    // NOTE: currently, `SpriteType` is fixed to be `FRIENDLY`
    NPCActor(
        GameContext* gameContext,
        SDL_Rect worldCoords
    );

    bool giveItem(
        std::shared_ptr<Item> item
    );

    void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    );

    void update(
        UpdateContext* updateContext
    );

    void draw(
        GameRenderer* renderer
    );

private:
    Inventory inventory;
};

#endif