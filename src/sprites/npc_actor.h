#ifndef _NPC_ACTOR_H
#define _NPC_ACTOR_H

#include "actor.h"
#include "input_event.h"
#include "input_handler.h"
#include "inventory.h"
#include "action.h"

// TODO: REMOVE
#include "patrol_action.h"
#include "follow_action.h"
#include "idle_action.h"
#include "wander_action.h"


class NPCActor : public Actor
{
public:
    // NOTE: currently, `SpriteType` only determines the
    // action to be executed. In the future, NPCActor will
    // only be an abstract parent class, and might not even
    // necessarily know the SpriteType of its child implementation.
    NPCActor(
        GameContext* gameContext,
        SpriteType spriteType,
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
    std::shared_ptr<Action> currAction;
};

#endif