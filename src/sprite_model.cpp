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