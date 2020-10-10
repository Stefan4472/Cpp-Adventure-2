#include "sprite_model.h"

SpriteModel::SpriteModel(
        TextureId idleImg,
        std::shared_ptr<Spritesheet> walkUpSheet,
        std::shared_ptr<Spritesheet> walkDownSheet,
        std::shared_ptr<Spritesheet> walkLeftSheet,
        std::shared_ptr<Spritesheet> walkRightSheet
) {
    this->idleImg = idleImg;
    this->walkUpSheet = walkUpSheet;
    this->walkDownSheet = walkDownSheet;
    this->walkLeftSheet = walkLeftSheet;
    this->walkRightSheet = walkRightSheet;
}

std::pair<TextureId, SDL_Rect> SpriteModel::getDrawInfo(TextureCache* textureCache)
{
    // For now, just return idleImg
    int img_width, img_height;
    std::tie(img_width, img_height) = 
        textureCache->getDimensions(idleImg);
    
    SDL_Rect source_rect = {
        0,
        0,
        img_width,
        img_height
    };
    return std::make_pair(
        idleImg,
        source_rect
    );
}