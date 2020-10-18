#include "sprite.h"

Sprite::Sprite(
        GameContext* gameContext,
        SpriteType spriteType, 
        int spriteID,
        std::shared_ptr<SpriteModel> spriteModel,
        // int hp,
        double worldX, 
        double worldY
) {
    this->gameContext = gameContext;
    this->spriteType = spriteType;
    this->id = spriteID;
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

int Sprite::getID()
{
    return id;
}

void Sprite::setInHandItem(std::shared_ptr<Item> item)
{
    inHandItem = item;
    // Propagate to `spriteModel`
    spriteModel->setInHandItem(item);
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

std::pair<int, int> Sprite::getTileCoords()
{
    return gameContext->engine->resolveTile(
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

void Sprite::walkUp(int numTiles)
{
    currWalkCommand = Direction::UP;
    goalWorldX = worldX;
    goalWorldY = worldY - numTiles * TextureCache::TILE_SIZE_PX;
    spriteModel->startMoving(Direction::UP);
}

void Sprite::walkDown(int numTiles)
{
    currWalkCommand = Direction::DOWN;
    goalWorldX = worldX;
    goalWorldY = worldY + numTiles * TextureCache::TILE_SIZE_PX;
    spriteModel->startMoving(Direction::DOWN);
}

void Sprite::walkLeft(int numTiles)
{
    currWalkCommand = Direction::LEFT;
    goalWorldX = worldX - numTiles * TextureCache::TILE_SIZE_PX;
    goalWorldY = worldY;
    spriteModel->startMoving(Direction::LEFT);
}

void Sprite::walkRight(int numTiles)
{
    currWalkCommand = Direction::RIGHT;
    goalWorldX = worldX + numTiles * TextureCache::TILE_SIZE_PX;
    goalWorldY = worldY;
    spriteModel->startMoving(Direction::RIGHT);
}

void Sprite::walkInDir(Direction direction, int numTiles)
{
    switch (direction)
    {
        case Direction::UP:
        {
            return walkUp(numTiles);
        }
        case Direction::DOWN:
        {
            return walkDown(numTiles);
        }
        case Direction::LEFT:
        {
            return walkLeft(numTiles);
        }
        case Direction::RIGHT:
        {
            return walkRight(numTiles);
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
    spriteModel->draw(
        renderer,
        worldX,
        worldY
    );
}