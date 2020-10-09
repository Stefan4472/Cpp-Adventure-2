#ifndef _PLAYER_SPRITE_H
#define _PLAYER_SPRITE_H

#include "memory.h"
#include "sprite.h"

// TODO: REMOVE
#include <iostream>

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
    
    void draw(SDL_Renderer* renderer);

private:
    SDL_Texture* spriteTexture;
    int textureWidth, textureHeight;
};

#endif