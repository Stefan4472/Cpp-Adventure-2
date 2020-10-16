#ifndef _SPRITE_MODEL_H
#define _SPRITE_MODEL_H

#include <memory>
#include "spritesheet.h"
#include "texture_cache.h"
#include "update_context.h"
#include "game_renderer.h"
#include "direction.h"
#include "item.h"


class SpriteModel
{
public:
    // Note: coded so that only one animation should be playing at a time
    // NOTE: ASSUMES ALL `IDLE` IMAGES ARE THE SAME DIMENSIONS,
    // AND THAT EACH FRAME OF PROVIDED SPRITESHEETS IS THE SAME DIMENSION
    // AS THE `IDLE` IMAGES.
    SpriteModel(
        TextureCache* textureCache,
        TextureId idleUpImg,
        TextureId idleDownImg,
        TextureId idleLeftImg,
        TextureId idleRightImg,
        std::shared_ptr<Spritesheet> walkUpSheet,
        std::shared_ptr<Spritesheet> walkDownSheet,
        std::shared_ptr<Spritesheet> walkLeftSheet,
        std::shared_ptr<Spritesheet> walkRightSheet
    );

    std::pair<int, int> getSpriteSize();
    
    void setInHandItem(std::shared_ptr<Item> inHandItem);
    
    // Start the moving-animation in specified direction.
    void startMoving(Direction newDirection);
    // Stop any moving-animation that is currently playing
    void stopMoving();
    // Whether there is a moving-animation currently playing
    bool getIsMoving();
    // Start facing in the specified direction.
    // NOTE: SpriteModel cannot be currently moving! 
    void faceDir(Direction direction);
    // Get direction the sprite is currently facing
    Direction getFacingDirection();

    void update(int msSincePrevUpdate);

    // Draw Model to the provided Renderer.
    // The coordinates provided mark the center of the bottom
    // of the sprite (i.e., where the sprite is standing). This
    // is done because the caller might not necessarily know
    // how big the drawn sprite will be.
    void draw(
        GameRenderer* renderer, 
        double wBottomCenterX, 
        double wBottomCenterY
    );

private:
    TextureCache* textureCache;
    TextureId idleUpImg;
    TextureId idleDownImg;
    TextureId idleLeftImg;
    TextureId idleRightImg;
    std::shared_ptr<Spritesheet> walkUpSheet;
    std::shared_ptr<Spritesheet> walkDownSheet;
    std::shared_ptr<Spritesheet> walkLeftSheet;
    std::shared_ptr<Spritesheet> walkRightSheet;

    // Item in the Sprite's hand. May be NULL.
    std::shared_ptr<Item> inHandItem;

    // Size of sprite, in pixels
    int widthPx, heightPx;
    
    Direction facingDirection;
    bool isWalking;

    void moveInDirection(
        Direction newDirection
    );

    void resetAnyPlaying();
    
    TextureId getImgForDirection(
        Direction direction
    );
    
    std::shared_ptr<Spritesheet> getSheetForDirection(
        Direction direction
    );
};

#endif