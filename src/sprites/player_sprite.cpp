#include "player_sprite.h"

PlayerSprite::PlayerSprite(
        std::shared_ptr<GameContext> gameContext, 
        SDL_Rect& baseTile
) : Sprite(gameContext, SpriteType::PLAYER, baseTile.x + baseTile.w / 2, baseTile.y + baseTile.h - 1)
{
    spriteTexture = gameContext->textureCache->getTexture(
        TextureId::SPRITE_FRONT
    );

    std::tie(textureWidth, textureHeight) = gameContext->textureCache->getDimensions(
        TextureId::SPRITE_FRONT
    );
    // TODO: START ON FRAME 1?
    // WE WANT THE ANIMATION TO START ON FRAME 1, BUT TO LOOP ON FRAME 0.
    walkUpSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_UP,
        std::vector<int>({100, 100, 100, 100}),
        true
    );
    walkDownSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_DOWN,
        std::vector<int>({100, 100, 100, 100}),
        true
    );
    walkLeftSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_LEFT,
        std::vector<int>({100, 100, 100, 100}),
        true
    );
    walkRightSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_RIGHT,
        std::vector<int>({100, 100, 100, 100}),
        true
    );
    spriteModel = std::make_shared<SpriteModel>(
        TextureId::SPRITE_BACK,
        TextureId::SPRITE_FRONT,
        TextureId::SPRITE_LEFT,
        TextureId::SPRITE_RIGHT,
        walkUpSpritesheet,
        walkDownSpritesheet,
        walkLeftSpritesheet,
        walkRightSpritesheet
    );

    walkPxPerMs = gameContext->tileSizePx * 1.0 / TILE_WALK_TIME_MS;
    currWalkCommand = WalkDirection::NONE;
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
    // Note that this may send a `nullptr` as `Item`. This is okay.
    // If there is no in-hand item, the user will attempt to pick
    // up a drop.
    // TODO: DETERMINE BASED ON CURRENT DIRECTION. FOR DEVELOPMENT, FOR NOW, WE WILL ALWAYS JUST DO THE TILE BELOW US
    updateContext->requestInteract(
        this,
        inventory.getSelectedItem().get(),
        curr_tile_x,
        curr_tile_y + 1
    );
}

void PlayerSprite::update(UpdateContext* updateContext)
{
    // No current movement input: see if there's a new one
    if (currWalkCommand == WalkDirection::NONE)
    {
        updateWalkCommand();
    }

    switch (currWalkCommand)
    {
        case WalkDirection::NONE:
        {
            break;
        }
        case WalkDirection::UP:
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
        case WalkDirection::DOWN:
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
        case WalkDirection::LEFT:
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
        case WalkDirection::RIGHT:
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

    spriteModel->update(updateContext);
}

void PlayerSprite::draw(GameRenderer* renderer)
{
    // Get drawing information from spriteModel
    TextureId texture_id;
    SDL_Rect src_rect;
    std::tie(texture_id, src_rect) = 
        spriteModel->getDrawInfo(gameContext->textureCache.get());

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
        case WalkDirection::NONE:
        {
            spriteModel->stopMoving();
            break;
        }
        case WalkDirection::UP:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y - 1))
            {
                goalWorldX = worldX;
                goalWorldY = worldY - gameContext->tileSizePx;
                spriteModel->moveUp();
            }
            break;
        }
        case WalkDirection::DOWN:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x, curr_tile_y + 1))
            {
                goalWorldX = worldX;
                goalWorldY = worldY + gameContext->tileSizePx;
                spriteModel->moveDown();
            }
            break;
        }
        case WalkDirection::LEFT:
        {
            if (gameContext->engine->isTileWalkable(curr_tile_x - 1, curr_tile_y))
            {
                goalWorldX = worldX - gameContext->tileSizePx;
                goalWorldY = worldY;
                spriteModel->moveLeft();
            }
            break;
        }
        case WalkDirection::RIGHT:
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
