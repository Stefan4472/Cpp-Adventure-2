#ifndef _PLAYER_SPRITE_H
#define _PLAYER_SPRITE_H

#include <memory>
// TODO: REMOVE
#include <iostream>
#include "sprite.h"
#include "spritesheet.h"

class PlayerSprite : public Sprite 
{
public:
    PlayerSprite(
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType, 
        double worldX, 
        double worldY
    );
    
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
    std::shared_ptr<Spritesheet> walkDownSpritesheet;
};

#endif