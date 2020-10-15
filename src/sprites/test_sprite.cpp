#include "test_sprite.h"

TestSprite::TestSprite(
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

SpriteType TestSprite::getSpriteType()
{
    return spriteType;
}

void TestSprite::setInHandItem(std::shared_ptr<Item> item)
{
    inHandItem = item;
}

double TestSprite::getWorldX()
{
    return worldX;
}

double TestSprite::getWorldY()
{
    return worldY;
}

std::pair<double, double> TestSprite::getWorldCoords()
{
    return std::make_pair(
        worldX,
        worldY
    );
}

Direction TestSprite::getFacingDirection()
{
    return spriteModel->getFacingDirection();
}

bool TestSprite::getIsWalking()
{
    return (currWalkCommand != Direction::NONE);
}

void TestSprite::walkUp(int numPx)
{
    currWalkCommand = Direction::UP;
    goalWorldX = worldX;
    goalWorldY = worldY - numPx;
    spriteModel->moveUp();
}

void TestSprite::walkDown(int numPx)
{
    currWalkCommand = Direction::DOWN;
    goalWorldX = worldX;
    goalWorldY = worldY + numPx;
    spriteModel->moveDown();
}

void TestSprite::walkLeft(int numPx)
{
    currWalkCommand = Direction::LEFT;
    goalWorldX = worldX - numPx;
    goalWorldY = worldY;
    spriteModel->moveLeft();
}

void TestSprite::walkRight(int numPx)
{
    currWalkCommand = Direction::RIGHT;
    goalWorldX = worldX + numPx;
    goalWorldY = worldY;
    spriteModel->moveRight();
}

void TestSprite::update(int msSincePrevUpdate)
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

void TestSprite::draw(GameRenderer* renderer)
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