#ifndef _SPRITE_MODEL_H
#define _SPRITE_MODEL_H

#include <memory>
#include "spritesheet.h"
#include "texture_cache.h"
#include "update_context.h"
#include "direction.h"


class SpriteModel
{
public:
    // Note: coded so that only one animation should be playing at a time
    // TODO: STORE REF TO INHANDITEM, SO WE CAN DRAW IT CORRECTLY
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
    
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void stopMoving();
    // Get direction the sprite is currently facing
    Direction getFacingDirection();

    void update(int msSincePrevUpdate);

    std::pair<TextureId, SDL_Rect> getDrawInfo();

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