#ifndef _SPRITE_MODEL_H
#define _SPRITE_MODEL_H

#include <memory>
#include "spritesheet.h"
#include "texture_cache.h"


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

    std::pair<TextureId, SDL_Rect> getDrawInfo(
            TextureCache* textureCache
    );

private:
    TextureId idleImg;
    std::shared_ptr<Spritesheet> walkUpSheet;
    std::shared_ptr<Spritesheet> walkDownSheet;
    std::shared_ptr<Spritesheet> walkLeftSheet;
    std::shared_ptr<Spritesheet> walkRightSheet;
};

#endif