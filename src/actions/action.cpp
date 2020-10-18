#include "action.h"

Action::Action(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) {
    this->gameContext = gameContext;
    this->sprite = sprite;
}

bool Action::requestMoveInDir(
        UpdateContext* updateContext,
        Direction direction
) {
    // Get current tile coordinates
    int my_tile_x, my_tile_y;
    std::tie(my_tile_x, my_tile_y) = sprite->getTileCoords();

    // Calculate desired tile coordinates
    int goal_tile_x, goal_tile_y;
    std::tie(goal_tile_x, goal_tile_y) = util::calcTileChange(
        my_tile_x,
        my_tile_y,
        direction
    );

    // Request to move to desired tile
    return updateContext->requestMoveToTile(
        sprite.get(),
        my_tile_x,
        my_tile_y,
        goal_tile_x,
        goal_tile_y
    );
}