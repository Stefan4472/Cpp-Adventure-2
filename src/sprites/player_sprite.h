#ifndef _PLAYER_SPRITE_H
#define _PLAYER_SPRITE_H

#include <memory>
// TODO: REMOVE
#include <iostream>
#include "sprite.h"
#include "spritesheet.h"
#include "sprite_model.h"
#include "walk_direction.h"
#include "input_event.h"
#include "input_handler.h"
#include "item.h"


class PlayerSprite : public Sprite 
{
public:
    PlayerSprite(
        std::shared_ptr<GameContext> gameContext, 
        SDL_Rect& baseTile
    );
    
    // How long it takes to walk the distance of one tile
    const int TILE_WALK_TIME_MS = 400;

    // Item in hand (may be NULL)
    // TODO: MAKE PRIVATE. CURRENTLY PUBLIC FOR TESTING/DEV
    std::shared_ptr<Item> inHandItem;

    void giveInput(EventId eventId, UpdateContext* updateContext);
    // Responds to "action" button pressed
    void executeAction(UpdateContext* updateContext);
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* renderer);

private:
    InputHandler inputHandler;
    // Number of pixels walked per millisecond
    double walkPxPerMs;

    SDL_Texture* spriteTexture;
    int textureWidth, textureHeight;
    std::shared_ptr<SpriteModel> spriteModel;
    std::shared_ptr<Spritesheet> walkDownSpritesheet;
    std::shared_ptr<Spritesheet> walkUpSpritesheet;
    std::shared_ptr<Spritesheet> walkLeftSpritesheet;
    std::shared_ptr<Spritesheet> walkRightSpritesheet;


    // Direction currently being walked in
    WalkDirection currWalkCommand;
    double goalWorldX, goalWorldY;

    void updateWalkCommand();
};

#endif