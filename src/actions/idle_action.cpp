#include "idle_action.h"

IdleAction::IdleAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) : Action(gameContext, sprite)
{

}

void IdleAction::start()
{
    // Start off facing in a random direction
    sprite->faceDir(getRandomDirection());
}

bool IdleAction::getIsFinished()
{
    return false;
}

void IdleAction::update(UpdateContext* updateContext)
{
    msSinceLastChange += updateContext->msSincePrevUpdate;
    // Time to potentially change direction
    if (msSinceLastChange >= CHANGE_DIR_TIME_MS)
    {
        // Simulate a 75% chance of re-picking a direction
        if (gameContext->engine->genRandInt1To100() <= 75)
        {
            sprite->faceDir(getRandomDirection());
        }
        msSinceLastChange = 0;
    }
}

Direction IdleAction::getRandomDirection()
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
