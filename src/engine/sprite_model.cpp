#include "sprite_model.h"

SpriteModel::SpriteModel(
        TextureId idleUpImg,
        TextureId idleDownImg,
        TextureId idleLeftImg,
        TextureId idleRightImg,
        std::shared_ptr<Spritesheet> walkUpSheet,
        std::shared_ptr<Spritesheet> walkDownSheet,
        std::shared_ptr<Spritesheet> walkLeftSheet,
        std::shared_ptr<Spritesheet> walkRightSheet
) {
    this->idleUpImg = idleUpImg;
    this->idleDownImg = idleDownImg;
    this->idleLeftImg = idleLeftImg;
    this->idleRightImg = idleRightImg;
    this->walkUpSheet = walkUpSheet;
    this->walkDownSheet = walkDownSheet;
    this->walkLeftSheet = walkLeftSheet;
    this->walkRightSheet = walkRightSheet;

    facingDirection = Direction::DOWN;
    isWalking = false;
}

Direction SpriteModel::getFacingDirection()
{
    return facingDirection;
}

void SpriteModel::moveUp()
{
    moveInDirection(Direction::UP);
}

void SpriteModel::moveDown()
{
    moveInDirection(Direction::DOWN);
}

void SpriteModel::moveLeft()
{
    moveInDirection(Direction::LEFT);
}

void SpriteModel::moveRight()
{
    moveInDirection(Direction::RIGHT);
}

void SpriteModel::stopMoving()
{
    resetAnyPlaying();
    isWalking = false;
}

void SpriteModel::update(UpdateContext* updateContext)
{
    if (isWalking)
    {
        getSheetForDirection(facingDirection)->update(
            updateContext->msSincePrevUpdate
        );
    }
}

std::pair<TextureId, SDL_Rect> SpriteModel::getDrawInfo(TextureCache* textureCache)
{
    // Currently walking: return frame from correct animation
    if (isWalking)
    {
        auto curr_sheet = getSheetForDirection(
            facingDirection
        );

        return std::make_pair(
            curr_sheet->getTextureID(),
            curr_sheet->getCurrentFrameSrc()
        );
    }
    // No animation playing: return idle image
    else
    {
        TextureId curr_img = getImgForDirection(
            facingDirection
        );

        int img_width, img_height;
        std::tie(img_width, img_height) = 
            textureCache->getDimensions(curr_img);
        
        SDL_Rect source_rect = {
            0,
            0,
            img_width,
            img_height
        };
        return std::make_pair(
            curr_img,
            source_rect
        );
    }
}

void SpriteModel::moveInDirection(Direction newDirection)
{
    resetAnyPlaying();
    facingDirection = newDirection;
    getSheetForDirection(newDirection)->start();
    isWalking = true;
}


void SpriteModel::resetAnyPlaying()
{
    if (isWalking)
    {
        auto curr_sheet = getSheetForDirection(
            facingDirection
        );

        curr_sheet->stop();
        curr_sheet->reset();
    }
}

TextureId SpriteModel::getImgForDirection(
        Direction direction
) {
    switch (direction)
    {
        case Direction::UP:
        {
            return idleUpImg;
        }
        case Direction::DOWN:
        {
            return idleDownImg;
        }
        case Direction::LEFT:
        {
            return idleLeftImg;
        }
        case Direction::RIGHT:
        {
            return idleRightImg;
        }
        default:
        {
            throw std::invalid_argument(
                std::string("No image for the provided direction ") +
                std::to_string(static_cast<int>(direction))
            );
        }
    }
}
    
std::shared_ptr<Spritesheet> SpriteModel::getSheetForDirection(
    Direction direction
) {
    switch (direction)
    {
        case Direction::UP:
        {
            return walkUpSheet;
        }
        case Direction::DOWN:
        {
            return walkDownSheet;
        }
        case Direction::LEFT:
        {
            return walkLeftSheet;
        }
        case Direction::RIGHT:
        {
            return walkRightSheet;
        }
        default:
        {
            throw std::invalid_argument(
                std::string("No image for the provided direction") +
                std::to_string(static_cast<int>(direction))
            );
        }
    }
}