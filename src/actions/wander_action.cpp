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

        bool is_path_blocked = false;
        int num_attempts = 0;
        do
        {
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
                is_path_blocked = false;
            }
            else
            {
                is_path_blocked = true;
            }
            num_attempts++;
        } while (is_path_blocked && num_attempts < 4);
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