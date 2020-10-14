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
    // TODO: THIS IS KIND OF CRUDELY PROGRAMMED, NEEDS SOME REVISION
    SpriteModel(
        TextureId idleUpImg,
        TextureId idleDownImg,
        TextureId idleLeftImg,
        TextureId idleRightImg,
        std::shared_ptr<Spritesheet> walkUpSheet,
        std::shared_ptr<Spritesheet> walkDownSheet,
        std::shared_ptr<Spritesheet> walkLeftSheet,
        std::shared_ptr<Spritesheet> walkRightSheet
    );

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void stopMoving();
    // Get direction the sprite is currently facing
    Direction getFacingDirection();

    void update(UpdateContext* updateContext);

    std::pair<TextureId, SDL_Rect> getDrawInfo(
            TextureCache* textureCache
    );

private:
    TextureId idleUpImg;
    TextureId idleDownImg;
    TextureId idleLeftImg;
    TextureId idleRightImg;
    std::shared_ptr<Spritesheet> walkUpSheet;
    std::shared_ptr<Spritesheet> walkDownSheet;
    std::shared_ptr<Spritesheet> walkLeftSheet;
    std::shared_ptr<Spritesheet> walkRightSheet;

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