#ifndef _SPRITE_MODEL_H
#define _SPRITE_MODEL_H

#include <memory>
#include "spritesheet.h"

class SpriteModel
{
public:
    SpriteModel(
        TextureId idleImg,
        std::shared_ptr<Spritesheet> walkUpSheet,
        std::shared_ptr<Spritesheet> walkDownSheet,
        std::shared_ptr<Spritesheet> walkLeftSheet,
        std::shared_ptr<Spritesheet> walkRightSheet
    );

private:
    TextureId idleImg;
    std::shared_ptr<Spritesheet> walkUpSheet;
    std::shared_ptr<Spritesheet> walkDownSheet;
    std::shared_ptr<Spritesheet> walkLeftSheet;
    std::shared_ptr<Spritesheet> walkRightSheet;
};

#endif