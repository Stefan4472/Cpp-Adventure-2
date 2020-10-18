#include "follow_action.h"

FollowAction::FollowAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) : Action(gameContext, sprite)
{

}

void FollowAction::start()
{
    
}

bool FollowAction::getIsFinished()
{
    return false;
}

void FollowAction::update(UpdateContext* updateContext)
{
    // Sprite has finished walking to current target:
    // Lookup player location, and move one block toward it.
    if (!sprite->getIsWalking())
    {
        int my_tile_x, my_tile_y;
        std::tie(my_tile_x, my_tile_y) = sprite->getTileCoords();

        int player_tile_x, player_tile_y;
        std::tie(player_tile_x, player_tile_y) = 
            gameContext->engine->getPlayerTile();

        int x_dist = player_tile_x - my_tile_x;
        int y_dist = player_tile_y - my_tile_y;

        // Calculate Manhattan tile distance
        int man_dist = std::abs(x_dist) + std::abs(y_dist);

        // Get closer if Manhattan distance greater than one tile
        if (man_dist > 1)
        {
            // Direction to move
            Direction goal_dir;
            // Tile coordinates to move to
            int goal_tile_x, goal_tile_y;

            // Determine on which axis we are farther away
            if (std::abs(x_dist) > std::abs(y_dist))
            {
                // Reduce x distance:
                if (x_dist > 0)
                {
                    // Move one tile right
                    goal_dir = Direction::RIGHT;
                    goal_tile_x = my_tile_x + 1;
                    goal_tile_y = my_tile_y;
                }
                else
                {
                    // Move one tile left
                    goal_dir = Direction::LEFT;
                    goal_tile_x = my_tile_x - 1;
                    goal_tile_y = my_tile_y;
                }
            }
            else
            {
                // Reduce y distance:
                if (y_dist > 0)
                {
                    // Move one tile down
                    goal_dir = Direction::DOWN;
                    goal_tile_x = my_tile_x;
                    goal_tile_y = my_tile_y + 1;
                }
                else
                {
                    // Move one tile up
                    goal_dir = Direction::UP;
                    goal_tile_x = my_tile_x;
                    goal_tile_y = my_tile_y - 1;
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
                    goal_dir, 
                    TextureCache::TILE_SIZE_PX
                );
            }
        }
    }
}