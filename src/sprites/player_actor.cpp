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
        updateWalkCommand(updateContext);
    }
}

void PlayerActor::updateWalkCommand(UpdateContext* updateContext)
{
    Direction direction_input = inputHandler.getNextWalkCommand();
    
    // Exit immediately if no direction input
    if (direction_input == Direction::NONE)
    {
        return;
    }

    // Get current tile coordinates
    int my_tile_x, my_tile_y;
    std::tie(my_tile_x, my_tile_y) = getTileCoords();

    // Calculate desired tile coordinates
    int goal_tile_x, goal_tile_y;
    std::tie(goal_tile_x, goal_tile_y) = util::calcTileChange(
        my_tile_x,
        my_tile_y,
        direction_input
    );

    // Request to move to desired tile
    bool can_move = updateContext->requestMoveToTile(
        getSprite().get(),
        my_tile_x,
        my_tile_y,
        goal_tile_x,
        goal_tile_y
    );

    // Execute command if we are clear to change tiles
    if (can_move)
    {
        sprite->walkInDir(
            direction_input, 
            TextureCache::TILE_SIZE_PX
        );
    }
    else
    {
        // TODO: PLAY WALKING ANIMATION, BUT DON'T SET MOVE GOAL, OTHERWISE
    }
}

void PlayerActor::draw(GameRenderer* renderer) 
{
    sprite->draw(renderer);
}