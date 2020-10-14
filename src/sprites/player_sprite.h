#ifndef _PLAYER_SPRITE_H
#define _PLAYER_SPRITE_H

#include <memory>
// TODO: REMOVE
#include <iostream>
#include "sprite.h"
#include "spritesheet.h"
#include "sprite_model.h"
#include "direction.h"
#include "input_event.h"
#include "input_handler.h"
#include "inventory.h"
#include "item.h"
#include "model_factory.h"


class PlayerSprite : public Sprite 
{
public:
    PlayerSprite(
        std::shared_ptr<GameContext> gameContext, 
        SDL_Rect& baseTile
    );
    
    // How long it takes to walk the distance of one tile
    const int TILE_WALK_TIME_MS = 400;

    void giveInput(EventId eventId, UpdateContext* updateContext);
    bool giveItem(std::shared_ptr<Item> item);
    // Responds to "action" button pressed
    void executeAction(UpdateContext* updateContext);
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* renderer);

private:
    InputHandler inputHandler;
    // Number of pixels walked per millisecond
    double walkPxPerMs;

    std::shared_ptr<SpriteModel> spriteModel;

    Inventory inventory;

    // Direction currently being walked in
    Direction currWalkCommand;
    double goalWorldX, goalWorldY;

    void updateWalkCommand();
};

#endif