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

void SpriteModel::moveUp()
{
    resetAnyPlaying();
    walkUpSheet->start();
}

void SpriteModel::moveDown()
{
    resetAnyPlaying();
    walkDownSheet->start();
}

void SpriteModel::moveLeft()
{
    resetAnyPlaying();
    walkLeftSheet->start();
}

void SpriteModel::moveRight()
{
    resetAnyPlaying();
    walkRightSheet->start();
}

void SpriteModel::stopMoving()
{
    resetAnyPlaying();
}

void SpriteModel::update(UpdateContext* updateContext)
{
    if (walkUpSheet->getIsPlaying())
    {
        walkUpSheet->update(updateContext->msSincePrevUpdate);
    }
    else if (walkDownSheet->getIsPlaying())
    {
        walkDownSheet->update(updateContext->msSincePrevUpdate);
    }
    else if (walkLeftSheet->getIsPlaying())
    {
        walkLeftSheet->update(updateContext->msSincePrevUpdate);
    }
    else if (walkRightSheet->getIsPlaying())
    {
        walkRightSheet->update(updateContext->msSincePrevUpdate);
    }
}

std::pair<TextureId, SDL_Rect> SpriteModel::getDrawInfo(TextureCache* textureCache)
{
    if (walkUpSheet->getIsPlaying())
    {
        return std::make_pair(
            walkUpSheet->getTextureID(),
            walkUpSheet->getCurrentFrameSrc()
        );
    }
    else if (walkDownSheet->getIsPlaying())
    {
        return std::make_pair(
            walkDownSheet->getTextureID(),
            walkDownSheet->getCurrentFrameSrc()
        );
    }
    else if (walkLeftSheet->getIsPlaying())
    {
        return std::make_pair(
            walkLeftSheet->getTextureID(),
            walkLeftSheet->getCurrentFrameSrc()
        );
    }
    else if (walkRightSheet->getIsPlaying())
    {
        return std::make_pair(
            walkRightSheet->getTextureID(),
            walkRightSheet->getCurrentFrameSrc()
        );
    }
    // No animation playing: return idleImg
    else
    {
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
}

void SpriteModel::resetAnyPlaying()
{
    if (walkUpSheet->getIsPlaying())
    {
        walkUpSheet->stop();
        walkUpSheet->reset();
    }
    if (walkDownSheet->getIsPlaying())
    {
        walkDownSheet->stop();
        walkDownSheet->reset();
    }
    if (walkLeftSheet->getIsPlaying())
    {
        walkLeftSheet->stop();
        walkLeftSheet->reset();
    }
    if (walkRightSheet->getIsPlaying())
    {
        walkRightSheet->stop();
        walkRightSheet->reset();
    }
}