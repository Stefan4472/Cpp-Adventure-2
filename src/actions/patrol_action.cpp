#include "patrol_action.h"

PatrolAction::PatrolAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) : Action(gameContext, sprite)
{
    tilesLeft = 0;
}

void PatrolAction::start()
{
    currDirection = Direction::DOWN;
    tilesLeft = 10;
}

bool PatrolAction::getIsFinished()
{
    return false;
}

void PatrolAction::update(UpdateContext* updateContext)
{
    // Sprite has finished walking one tile
    if (!sprite->getIsWalking())
    {
        // Time to change direction
        if (tilesLeft == 0)
        {
            currDirection = util::invertDirection(currDirection);
            tilesLeft = 10;
        }

        // Request movement
        if (requestMoveInDir(updateContext, currDirection))
        {
            sprite->walkInDir(
                currDirection, 
                TextureCache::TILE_SIZE_PX
            );
            tilesLeft--;
        }
        else
        {
            // Blocked path: do nothing
        }
    }
}