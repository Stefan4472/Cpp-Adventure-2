#include "player_sprite.h"

PlayerSprite::PlayerSprite(
        GameContext* gameContext, 
        SDL_Rect baseTile
) : Sprite(gameContext, SpriteType::PLAYER, baseTile.x + baseTile.w / 2, baseTile.y + baseTile.h - 1)
{
    spriteModel = ModelFactory::createSpriteModel(
        gameContext->textureCache.get(),
        SpriteType::PLAYER
    );

    walkPxPerMs = gameContext->tileSizePx * 1.0 / TILE_WALK_TIME_MS;
    currWalkCommand = Direction::NONE;
    goalWorldX = worldX;
    goalWorldY = worldY;
}

void PlayerSprite::giveInput(EventId eventId, UpdateContext* updateContext)
{
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

bool PlayerSprite::giveItem(std::shared_ptr<Item> item)
{
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

void PlayerSprite::executeAction(UpdateContext* updateContext)
{
    std::cout << "Player should execute action" << std::endl;
    // TODO: "Punch" if no inHandItem?
    // Get current tile
    int curr_tile_x, curr_tile_y;
    std::tie(curr_tile_x, curr_tile_y) = 
        gameContext->engine->resolveTile(worldX, worldY);

    // Determine the tile to interact with.
    int interact_tile_x, interact_tile_y;
    switch (spriteModel->getFacingDirection())
    {
        case Direction::UP:
        {
            interact_tile_x = curr_tile_x;
            interact_tile_y = curr_tile_y - 1;
            break;
        }
        case Direction::DOWN:
        {
            interact_tile_x = curr_tile_x;
            interact_tile_y = curr_tile_y + 1;
            break;
        }
        case Direction::LEFT:
        {
            interact_tile_x = curr_tile_x - 1;
            interact_tile_y = curr_tile_y;
            break;
        }
        case Direction::RIGHT:
        {
            interact_tile_x = curr_tile_x + 1;
            interact_tile_y = curr_tile_y;
            break;
        }
    }

    // Request the interaction.
    // Note that this may send a `nullptr` as `Item`. This is okay.
    // If there is no in-hand item, the user will attempt to pick
    // up a drop.
    updateContext->requestInteract(
        this,
        inventory.getSelectedItem().get(),
        interact_tile_x,
        interact_tile_y
    );
}

void PlayerSprite::update(UpdateContext* updateContext)
{
    // No current movement input: see if there's a new one
    if (currWalkCommand == Direction::NONE)
    {
        updateWalkCommand();
    }

    switch (currWalkCommand)
    {
        case Direction::NONE:
        {
            break;
        }
        case Direction::UP:
        {
            double px_to_move = 
                walkPxPerMs * updateContext->msSincePrevUpdate;
            worldY -= px_to_move;
            // Check for completion (and fix possible overshoot)
            if (worldY <= goalWorldY)
            {
                worldY = goalWorldY;
                updateWalkCommand();
            }
            break;
        }
        case Direction::DOWN:
        {
            double px_to_move = 
                walkPxPerMs * updateContext->msSincePrevUpdate;
            worldY += px_to_move;
            // Check for completion (and fix possible overshoot)
            if (worldY >= goalWorldY)
            {
                worldY = goalWorldY;
                updateWalkCommand();
            }
            break;
        }
        case Direction::LEFT:
        {
            double px_to_move = 
                walkPxPerMs * updateContext->msSincePrevUpdate;
            worldX -= px_to_move;
            // Check for completion (and fix possible overshoot)
            if (worldX <= goalWorldX)
            {
                worldX = goalWorldX;
                updateWalkCommand();
            }
            break;
        }
        case Direction::RIGHT:
        {
            double px_to_move = 
                walkPxPerMs * updateContext->msSincePrevUpdate;
            worldX += px_to_move;
            // Check for completion (and fix possible overshoot)
            if (worldX >= goalWorldX)
            {
                worldX = goalWorldX;
                updateWalkCommand();
            }
            break;
        }
    }

    spriteModel->update(updateContext->msSincePrevUpdate);
}

void PlayerSprite::draw(GameRenderer* renderer)
{
    // Get drawing information from spriteModel
    TextureId texture_id;
    SDL_Rect src_rect;
    std::tie(texture_id, src_rect) = spriteModel->getDrawInfo();

    renderer->drawToWorld(
        texture_id,
        src_rect,
        worldX - src_rect.w / 2,
        worldY - src_rect.h
    );

    // Draw in-hand item
    // (currently drawing at an offset so as to give a rough 
    // approximation that the item is actually in the Sprite's 
    // hand.
    auto inHandItem = inventory.getSelectedItem();
    if (inHandItem)
    {
        renderer->drawToWorld(
            inHandItem->getTextureId(),
            worldX + src_rect.w / 2 - 10,
            worldY - src_rect.h / 2 - 10
        );
    }
}

void PlayerSprite::updateWalkCommand()
{
    currWalkCommand = inputHandler.getNextWalkCommand();
    
    int curr_tile_x, curr_tile_y;
    std::tie(curr_tile_x, curr_tile_y) = 
        gameContext->engine->resolveTile(worldX, worldY);

    switch (currWalkCommand)
    {
        case Direction::NONE:
        {
            spriteModel->stopMoving();
            break;
        }
        case Direction::UP:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y - 1))
            {
                goalWorldX = worldX;
                goalWorldY = worldY - gameContext->tileSizePx;
                spriteModel->moveUp();
            }
            break;
        }
        case Direction::DOWN:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y + 1))
            {
                goalWorldX = worldX;
                goalWorldY = worldY + gameContext->tileSizePx;
                spriteModel->moveDown();
            }
            break;
        }
        case Direction::LEFT:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x - 1, curr_tile_y))
            {
                goalWorldX = worldX - gameContext->tileSizePx;
                goalWorldY = worldY;
                spriteModel->moveLeft();
            }
            break;
        }
        case Direction::RIGHT:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x + 1, curr_tile_y))
            {
                goalWorldX = worldX + gameContext->tileSizePx;
                goalWorldY = worldY;
                spriteModel->moveRight();
            }
            break;
        }    
    }
}
