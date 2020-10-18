#ifndef _PLAYER_ACTOR_H
#define _PLAYER_ACTOR_H

#include "actor.h"
#include "input_event.h"
#include "input_handler.h"
#include "inventory.h"
#include "util.h"

// TODO: REMOVE?
#include <iostream>

class PlayerActor : public Actor
{
public:
    PlayerActor(
        GameContext* gameContext,
        SDL_Rect worldCoords
    );

    void giveInput(
        EventId eventId, 
        UpdateContext* updateContext
    );

    bool giveItem(
        std::shared_ptr<Item> item
    );

    // Responds to "action" button pressed
    void executeAction(
        UpdateContext* updateContext
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
    InputHandler inputHandler;
    Inventory inventory;
    // Direction currently being walked in
    // Direction currWalkCommand;
    void updateWalkCommand(
        UpdateContext* updateContext
    );
};
#endif