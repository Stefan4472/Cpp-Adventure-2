#include "npc_actor.h"

NPCActor::NPCActor(
        GameContext* gameContext,
        SDL_Rect worldCoords
) : Actor(gameContext, SpriteType::FRIENDLY, worldCoords)
{
    currAction = std::make_shared<Action>(sprite);
    currAction->start();
}

bool NPCActor::giveItem(std::shared_ptr<Item> item) {
    if (inventory.checkIsFull())
    {
        return false;
    }
    else
    {
        inventory.giveItem(item);
        return true;
    }
}

void NPCActor::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    // TODO
}

void NPCActor::update(UpdateContext* updateContext) 
{
    // Update Sprite
    sprite->update(updateContext->msSincePrevUpdate);

    currAction->update(updateContext);

    // Not walking: see if there's new input
    // if (!sprite->getIsWalking())
    // {
    //     updateWalkCommand();
    // }
}

// void NPCActor::updateWalkCommand()
// {
//     Direction direction_input = inputHandler.getNextWalkCommand();
    
//     int curr_tile_x, curr_tile_y;
//     std::tie(curr_tile_x, curr_tile_y) = getTileCoords();

//     // For each case: check that the adjacent tile is walkable,
//     // then set a goal for one tile in the desired direction.
//     switch (direction_input)
//     {
//         case Direction::UP:
//         {
//             if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y - 1))
//             {
//                 sprite->walkUp(TextureCache::TILE_SIZE_PX);
//             }
//             break;
//         }
//         case Direction::DOWN:
//         {
//             if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y + 1))
//             {
//                 sprite->walkDown(TextureCache::TILE_SIZE_PX);
//             }
//             break;
//         }
//         case Direction::LEFT:
//         {
//             if (gameContext->engine->isTileWalkable(curr_tile_x - 1, curr_tile_y))
//             {
//                 sprite->walkLeft(TextureCache::TILE_SIZE_PX);
//             }
//             break;
//         }
//         case Direction::RIGHT:
//         {
//             if (gameContext->engine->isTileWalkable(curr_tile_x + 1, curr_tile_y))
//             {
//                 sprite->walkRight(TextureCache::TILE_SIZE_PX);
//             }
//             break;
//         }
//         case Direction::NONE:
//         {
//             break;
//         }
//     }
// }

void NPCActor::draw(GameRenderer* renderer) 
{
    // int tile_x, tile_y;
    // std::tie(tile_x, tile_y) = getTileCoords();
    sprite->draw(renderer);
}