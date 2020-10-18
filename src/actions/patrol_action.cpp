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
            if (currDirection == Direction::DOWN)
            {
                currDirection = Direction::UP;
            }
            else
            {
                currDirection = Direction::DOWN;
            }
            tilesLeft = 10;
        }

        // Get our tile coordinates
        int my_tile_x, my_tile_y;
        std::tie(my_tile_x, my_tile_y) = sprite->getTileCoords();

        // Tile coordinates to move to
        int goal_tile_x, goal_tile_y;

        switch (currDirection)
        {
            case Direction::UP:
            {
                goal_tile_x = my_tile_x;
                goal_tile_y = my_tile_y - 1;
                break;
            }
            case Direction::DOWN:
            {
                goal_tile_x = my_tile_x;
                goal_tile_y = my_tile_y + 1;
                break;
            }
            case Direction::LEFT:
            {
                goal_tile_x = my_tile_x - 1;
                goal_tile_y = my_tile_y;
                break;
            }
            case Direction::RIGHT:
            {
                goal_tile_x = my_tile_x + 1;
                goal_tile_y = my_tile_y;
                break;
            }
            default:
            {
                throw std::runtime_error(
                    "Unhandled case: Programmer error"
                );
            }
        }
        
        // Request to change tiles
        bool can_move = updateContext->requestMoveToTile(
            sprite.get(),
            my_tile_x,
            my_tile_y,
            goal_tile_x,
            goal_tile_y
        );

        // Move one tile in desired direction
        if (can_move)
        {
            sprite->walkInDir(
                currDirection, 
                TextureCache::TILE_SIZE_PX
            );
            tilesLeft--;
        }
    }
}