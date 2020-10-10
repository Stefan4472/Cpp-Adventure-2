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


class PlayerSprite : public Sprite 
{
public:
    PlayerSprite(
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType, 
        double worldX, 
        double worldY
    );
    
    void giveInput(EventId eventId);
    
    // Move by one tile
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void updateCoords();
    
    void update(UpdateContext* updateContext);
    void draw(SDL_Renderer* renderer);

private:
    SDL_Texture* spriteTexture;
    int textureWidth, textureHeight;
    std::shared_ptr<SpriteModel> spriteModel;
    std::shared_ptr<Spritesheet> walkDownSpritesheet;
    std::shared_ptr<Spritesheet> walkUpSpritesheet;
    std::shared_ptr<Spritesheet> walkLeftSpritesheet;
    std::shared_ptr<Spritesheet> walkRightSpritesheet;

    // Direction currently being walked in
    WalkDirection walkDirection = WalkDirection::NONE;
    // How long does it take to walk the distance of one tile?
    const int TILE_WALK_TIME_MS = 800;
};

#endif