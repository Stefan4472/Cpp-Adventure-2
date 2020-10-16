#include "sprite.h"

Sprite::Sprite(
        SpriteType spriteType, 
        std::shared_ptr<SpriteModel> spriteModel,
        // int hp,
        double worldX, 
        double worldY
) {
    this->spriteType = spriteType;
    this->spriteModel = spriteModel;
    this->worldX = worldX;
    this->worldY = worldY;

    walkPxPerMs = TextureCache::TILE_SIZE_PX * 1.0 / TILE_WALK_TIME_MS;
    currWalkCommand = Direction::NONE;
    goalWorldX = worldX;
    goalWorldY = worldY;
}

SpriteType Sprite::getSpriteType()
{
    return spriteType;
}

void Sprite::setInHandItem(std::shared_ptr<Item> item)
{
    inHandItem = item;
}

double Sprite::getWorldX()
{
    return worldX;
}

double Sprite::getWorldY()
{
    return worldY;
}

std::pair<double, double> Sprite::getWorldCoords()
{
    return std::make_pair(
        worldX,
        worldY
    );
}

Direction Sprite::getFacingDirection()
{
    return spriteModel->getFacingDirection();
}

bool Sprite::getIsWalking()
{
    return (currWalkCommand != Direction::NONE);
}

void Sprite::walkUp(int numPx)
{
    currWalkCommand = Direction::UP;
    goalWorldX = worldX;
    goalWorldY = worldY - numPx;
    spriteModel->startMoving(Direction::UP);
}

void Sprite::walkDown(int numPx)
{
    currWalkCommand = Direction::DOWN;
    goalWorldX = worldX;
    goalWorldY = worldY + numPx;
    spriteModel->startMoving(Direction::DOWN);
}

void Sprite::walkLeft(int numPx)
{
    currWalkCommand = Direction::LEFT;
    goalWorldX = worldX - numPx;
    goalWorldY = worldY;
    spriteModel->startMoving(Direction::LEFT);
}

void Sprite::walkRight(int numPx)
{
    currWalkCommand = Direction::RIGHT;
    goalWorldX = worldX + numPx;
    goalWorldY = worldY;
    spriteModel->startMoving(Direction::RIGHT);
}

void Sprite::walkInDir(Direction direction, int numPx)
{
    switch (direction)
    {
        case Direction::UP:
        {
            return walkUp(numPx);
        }
        case Direction::DOWN:
        {
            return walkDown(numPx);
        }
        case Direction::LEFT:
        {
            return walkLeft(numPx);
        }
        case Direction::RIGHT:
        {
            return walkRight(numPx);
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported walk direction ") +
                std::to_string(static_cast<int>(direction))
            );
        }
    }
}

void Sprite::faceDir(Direction direction)
{
    spriteModel->faceDir(direction);
}

void Sprite::update(int msSincePrevUpdate)
{
    // Move sprite, if currently walking
    switch (currWalkCommand)
    {
        case Direction::UP:
        {
            worldY -= walkPxPerMs * msSincePrevUpdate;
            // Check for completion (and fix possible overshoot)
            if (worldY <= goalWorldY)
            {
                worldY = goalWorldY;
                currWalkCommand = Direction::NONE;
                spriteModel->stopMoving();
            }
            break;
        }
        case Direction::DOWN:
        {
            worldY += walkPxPerMs * msSincePrevUpdate;
            // Check for completion (and fix possible overshoot)
            if (worldY >= goalWorldY)
            {
                worldY = goalWorldY;
                currWalkCommand = Direction::NONE;
                spriteModel->stopMoving();
            }
            break;
        }
        case Direction::LEFT:
        {
            worldX -= walkPxPerMs * msSincePrevUpdate;
            // Check for completion (and fix possible overshoot)
            if (worldX <= goalWorldX)
            {
                worldX = goalWorldX;
                currWalkCommand = Direction::NONE;
                spriteModel->stopMoving();
            }
            break;
        }
        case Direction::RIGHT:
        {
            worldX += walkPxPerMs * msSincePrevUpdate;
            // Check for completion (and fix possible overshoot)
            if (worldX >= goalWorldX)
            {
                worldX = goalWorldX;
                currWalkCommand = Direction::NONE;
                spriteModel->stopMoving();
            }
            break;
        }
        case Direction::NONE:
        {
            break;
        }
    }

    // Update model
    spriteModel->update(msSincePrevUpdate);
}

void Sprite::draw(GameRenderer* renderer)
{
    // Get drawing information from spriteModel
    TextureId texture_id;
    SDL_Rect src_rect;
    std::tie(texture_id, src_rect) = spriteModel->getDrawInfo();

    // Draw model
    renderer->drawToWorld(
        texture_id,
        src_rect,
        worldX - src_rect.w / 2,
        worldY - src_rect.h
    );

    // Draw in-hand item
    // (currently drawing at an offset so as to give a rough 
    // approximation that the item is actually in the Sprite's 
    // hand.
    if (inHandItem)
    {
        renderer->drawToWorld(
            inHandItem->getTextureId(),
            worldX + src_rect.w / 2 - 10,
            worldY - src_rect.h / 2 - 10
        );
    }
}