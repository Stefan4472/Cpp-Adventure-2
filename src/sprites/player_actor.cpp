#include "player_actor.h"

PlayerActor::PlayerActor(
        GameContext* gameContext,
        SDL_Rect worldCoords
) : Actor(gameContext, SpriteType::PLAYER, worldCoords)
{

}

void PlayerActor::giveInput(
        EventId eventId, 
        UpdateContext* updateContext
) {
    std::cout << gameContext->engine->genRandInt1To100() << std::endl;
    if (eventId == EventId::PRESS_ACTION)
    {
        executeAction(updateContext);
    }
    else if (eventId == EventId::ROTATE_INVENTORY)
    {
        inventory.rotateToNextItem();
    }
    else
    {
        inputHandler.giveInput(eventId);
    }
}

bool PlayerActor::giveItem(std::shared_ptr<Item> item) {
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

void PlayerActor::executeAction(UpdateContext* updateContext) {
    std::cout << "Player should execute action" << std::endl;
    // TODO: "Punch" if no inHandItem?
    
    int interact_tile_x, interact_tile_y;
    std::tie(interact_tile_x, interact_tile_y) = getFacedTile();

    // Request the interaction.
    // Note that this may send a `nullptr` as `Item`. This is okay.
    // If there is no in-hand item, the user will attempt to pick
    // up a drop.
    updateContext->requestInteract(
        sprite.get(),
        inventory.getSelectedItem().get(),
        interact_tile_x,
        interact_tile_y
    );
}

void PlayerActor::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    // TODO
}

void PlayerActor::update(UpdateContext* updateContext) 
{
    // Make sure we've given the Sprite our `inHandItem`
    sprite->setInHandItem(inventory.getSelectedItem());

    // Update Sprite
    sprite->update(updateContext->msSincePrevUpdate);

    // Not walking: see if there's new input
    if (!sprite->getIsWalking())
    {
        updateWalkCommand();
    }
}

void PlayerActor::updateWalkCommand()
{
    Direction direction_input = inputHandler.getNextWalkCommand();
    
    int curr_tile_x, curr_tile_y;
    std::tie(curr_tile_x, curr_tile_y) = getTileCoords();

    // For each case: check that the adjacent tile is walkable,
    // then set a goal for one tile in the desired direction.
    switch (direction_input)
    {
        case Direction::UP:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y - 1))
            {
                sprite->walkUp(TextureCache::TILE_SIZE_PX);
            }
            break;
        }
        case Direction::DOWN:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y + 1))
            {
                sprite->walkDown(TextureCache::TILE_SIZE_PX);
            }
            break;
        }
        case Direction::LEFT:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x - 1, curr_tile_y))
            {
                sprite->walkLeft(TextureCache::TILE_SIZE_PX);
            }
            break;
        }
        case Direction::RIGHT:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x + 1, curr_tile_y))
            {
                sprite->walkRight(TextureCache::TILE_SIZE_PX);
            }
            break;
        }
        case Direction::NONE:
        {
            break;
        }
    }
}

void PlayerActor::draw(GameRenderer* renderer) 
{
    sprite->draw(renderer);
}