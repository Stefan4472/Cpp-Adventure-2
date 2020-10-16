#include "patrol_action.h"

PatrolAction::PatrolAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) : Action(gameContext, sprite)
{

}

void PatrolAction::start()
{
    currDirection = Direction::DOWN;
    sprite->walkDown(TextureCache::TILE_SIZE_PX * 10);
}

bool PatrolAction::getIsFinished()
{
    return false;
}

void PatrolAction::update(UpdateContext* updateContext)
{
    // Sprite has finished walking to current target
    if (!sprite->getIsWalking())
    {
        // Set new target
        if (currDirection == Direction::DOWN)
        {
            currDirection = Direction::UP;
            sprite->walkUp(TextureCache::TILE_SIZE_PX * 10);
        }
        else
        {
            currDirection = Direction::DOWN;
            sprite->walkDown(TextureCache::TILE_SIZE_PX * 10);
        }
        
    }
}