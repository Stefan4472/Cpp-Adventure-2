#ifndef _TEST_SPRITE_H
#define _TEST_SPRITE_H

#include <SDL2/SDL.h>
#include <memory>
#include "game_context.h"
#include "update_context.h"
#include "game_renderer.h"
#include "sprite_type.h"
#include "sprite_model.h"
#include "item.h"

class TestSprite
{
public:
    TestSprite(
        SpriteType spriteType, 
        std::shared_ptr<SpriteModel> spriteModel,
        // int hp,
        double worldX, 
        double worldY
    );

    // How long it takes to walk the distance of one tile
    const int TILE_WALK_TIME_MS = 400;

    SpriteType getSpriteType();
    
    void setInHandItem(std::shared_ptr<Item> item);

    double getWorldX();
    double getWorldY();
    std::pair<double, double> getWorldCoords();

    Direction getFacingDirection();
    
    // TODO    
    // int getHp();

    // NOTE: ALWAYS MAKE SURE `ISWALKING()` IS FALSE BEFORE SENDING
    // THE NEXT WALK COMMAND! OTHERWISE, THE SPRITE WILL NO LONGER
    // BE TILE-ALIGNED
    bool getIsWalking();

    // void walkOneTileUp();
    // void walkOneTileDown();
    // void walkOneTileLeft();
    // void walkOneTileRight();

    // OR?
    void walkUp(int numPx);
    void walkDown(int numPx);
    void walkLeft(int numPx);
    void walkRight(int numPx);

    // Update
    void update(int msSincePrevUpdate);
    
    // Draw self onto provided renderer
    // TODO: THIS WILL BE CHANGED IN FAVOR OF RETURNING A LIST
    // OF DRAW COMMANDS, OR TO AT LEAST PROVIDE A BOUNDING BOX.
    // THAT WAY, THE ACTOR CAN DRAW A HEALTHBAR, PARTICLES, ETC.
    // ON THE SPRITE
    void draw(GameRenderer* renderer);

protected:
    SpriteType spriteType;
    
    // World coordinates
    double worldX, worldY;

    std::shared_ptr<Item> inHandItem;

    std::shared_ptr<SpriteModel> spriteModel;

    // Number of pixels walked per millisecond
    double walkPxPerMs;
    
    // Direction currently being walked in
    Direction currWalkCommand;
    double goalWorldX, goalWorldY;
};

#endif