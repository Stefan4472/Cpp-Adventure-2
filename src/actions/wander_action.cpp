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
}

bool WanderAction::getIsFinished()
{
    return false;
}

void WanderAction::update(UpdateContext* updateContext)
{
    // Sprite has finished walking one direction in `currDirection`
    // TODO: THIS CODE IS NOT *TECHNICALLY* 100% CORRECT, COULD BE IMPROVED
    if (!sprite->getIsWalking())
    {
        if (tilesLeft)
        {
            tilesLeft--;
        }
        // Sprite has now walked the desired number of tiles:
        // randomly pick new direction and new distance
        if (tilesLeft == 0)
        {
            currDirection = genRandomDirection();
            tilesLeft = genRandomDistance();
        }

        // In any case: attempt to move in desired direction
        bool move_success = false;
        int num_attempts = 0;
        while (!move_success && num_attempts < 5)
        {
            if (requestMoveInDir(updateContext, currDirection))
            {
                sprite->walkInDir(currDirection, 1);
                move_success = true;
            }
            else
            {
                // Try changing direction
                currDirection = genRandomDirection();
            }
            num_attempts++;
        }
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

// void WanderAction::handlePathBlocked()
// {
    
// }