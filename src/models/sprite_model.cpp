#include "sprite_model.h"

SpriteModel::SpriteModel(
        TextureCache* textureCache,
        TextureId idleUpImg,
        TextureId idleDownImg,
        TextureId idleLeftImg,
        TextureId idleRightImg,
        std::shared_ptr<Spritesheet> walkUpSheet,
        std::shared_ptr<Spritesheet> walkDownSheet,
        std::shared_ptr<Spritesheet> walkLeftSheet,
        std::shared_ptr<Spritesheet> walkRightSheet
) {
    this->textureCache = textureCache;
    this->idleUpImg = idleUpImg;
    this->idleDownImg = idleDownImg;
    this->idleLeftImg = idleLeftImg;
    this->idleRightImg = idleRightImg;
    this->walkUpSheet = walkUpSheet;
    this->walkDownSheet = walkDownSheet;
    this->walkLeftSheet = walkLeftSheet;
    this->walkRightSheet = walkRightSheet;

    std::tie(widthPx, heightPx) = textureCache->getDimensions(
        idleUpImg
    );

    facingDirection = Direction::DOWN;
    isWalking = false;
}

std::pair<int, int> SpriteModel::getSpriteSize()
{
    return std::make_pair(
        widthPx,
        heightPx
    );
}

void SpriteModel::setInHandItem(std::shared_ptr<Item> inHandItem)
{
    this->inHandItem = inHandItem;
}

void SpriteModel::startMoving(Direction newDirection)
{
    resetAnyPlaying();
    facingDirection = newDirection;
    getSheetForDirection(newDirection)->start();
    isWalking = true;
}

void SpriteModel::stopMoving()
{
    resetAnyPlaying();
    isWalking = false;
}

bool SpriteModel::getIsMoving()
{
    return isWalking;
}

void SpriteModel::faceDir(Direction direction)
{
    if (getIsMoving())
    {
        throw std::runtime_error(
            "Can't use this method while Sprite is moving"
        );
    }
    else
    {
        facingDirection = direction;
    }
}

Direction SpriteModel::getFacingDirection()
{
    return facingDirection;
}

void SpriteModel::update(int msSincePrevUpdate)
{
    if (isWalking)
    {
        getSheetForDirection(facingDirection)->update(
            msSincePrevUpdate
        );
    }
}

std::pair<TextureId, SDL_Rect> SpriteModel::getDrawInfo()
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

        SDL_Rect source_rect = {
            0,
            0,
            widthPx,
            heightPx
        };

        return std::make_pair(
            curr_img,
            source_rect
        );
    }
}

void SpriteModel::draw(
        GameRenderer* renderer, 
        double wBottomCenterX, 
        double wBottomCenterY
) {
    TextureId texture_id;
    SDL_Rect source_rect;

    // Currently walking: get animation frame
    if (isWalking)
    {
        auto curr_sheet = getSheetForDirection(
            facingDirection
        );
        texture_id = curr_sheet->getTextureID();
        source_rect = curr_sheet->getCurrentFrameSrc();
    }
    // No animation playing: get idle image
    else
    {
        texture_id = getImgForDirection(facingDirection);
        source_rect = {0, 0, widthPx, heightPx};
    }

    // Draw base image
    renderer->drawToWorld(
        texture_id,
        source_rect,
        wBottomCenterX - source_rect.w / 2,
        wBottomCenterY - source_rect.h
    );

    // Draw in-hand item
    // (currently drawing at an offset so as to give a rough 
    // approximation that the item is actually in the Sprite's 
    // hand.
    if (inHandItem)
    {
        renderer->drawToWorld(
            inHandItem->getTextureId(),
            wBottomCenterX + source_rect.w / 2 - 10,
            wBottomCenterY - source_rect.h / 2 - 10
        );
    }
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