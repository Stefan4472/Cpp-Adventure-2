#include "wander_action.h"

WanderAction::WanderAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) : Action(gameContext, sprite)
{

}

void WanderAction::start()
{
    currDirection = genRandomDirection();
    tilesLeft = genRandomDistance();
    sprite->walkInDir(currDirection, TextureCache::TILE_SIZE_PX);
}

bool WanderAction::getIsFinished()
{
    return false;
}

void WanderAction::update(UpdateContext* updateContext)
{
    // Sprite has finished walking one direction in `currDirection`
    if (!sprite->getIsWalking())
    {
        tilesLeft--;
        // Sprite has now walked the desired number of tiles:
        // generate new direction and new distance
        if (tilesLeft == 0)
        {
            currDirection = genRandomDirection();
            tilesLeft = genRandomDistance();
        }
        // Start walking one tile in the desired direction
        sprite->walkInDir(currDirection, TextureCache::TILE_SIZE_PX);
    }
}

Direction WanderAction::genRandomDirection()
{
    int rand = gameContext->engine->genRandInt1To100();
    if (rand >= 75)
    {
        return Direction::UP;
    }
    else if (rand >= 50)
    {
        return Direction::DOWN;
    }
    else if (rand >= 25)
    {
        return Direction::LEFT;
    }
    else
    {
        return Direction::RIGHT;
    }
}

int WanderAction::genRandomDistance()
{
    // Generate random distance from 1 to 6
    return 1 + gameContext->engine->genRandInt1To100() / 20;
}