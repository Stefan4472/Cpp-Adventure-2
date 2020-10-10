#include "player_sprite.h"

PlayerSprite::PlayerSprite(
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType, 
        double worldX, 
        double worldY
) : Sprite(gameContext, SpriteType::PLAYER, worldX, worldY)
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
        TextureId::SPRITE_FRONT,
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

void PlayerSprite::giveInput(EventId eventId)
{
    inputHandler.giveInput(eventId);
}

// void PlayerSprite::updateCoords()
// {
//     worldX = tileX * gameContext->tileSizePx;
//     worldY = tileY * gameContext->tileSizePx;
//     // std::cout << worldX << ", " << worldY << std::endl;
// }

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

    // Create destination rectangle. Draw to correct world coordinates
    // SDL_Rect dest_rect = {
    //     static_cast<int>(worldX),
    //     static_cast<int>(worldY - src_rect.h),
    //     src_rect.w,
    //     src_rect.h
    // };

    renderer->drawToWorld(
        texture_id,
        src_rect,
        worldX,
        worldY - src_rect.h
    );
    // SDL_RenderCopy(
    //     renderer,
    //     gameContext->textureCache->getTexture(texture_id),
    //     &src_rect,
    //     &dest_rect
    // );
}

void PlayerSprite::updateWalkCommand()
{
    currWalkCommand = inputHandler.getNextWalkCommand();
    switch (currWalkCommand)
    {
        case WalkDirection::NONE:
        {
            spriteModel->stopMoving();
            break;
        }
        case WalkDirection::UP:
        {
            goalWorldX = worldX;
            goalWorldY = worldY - gameContext->tileSizePx;
            spriteModel->moveUp();
            break;
        }
        case WalkDirection::DOWN:
        {
            goalWorldX = worldX;
            goalWorldY = worldY + gameContext->tileSizePx;
            spriteModel->moveDown();
            break;
        }
        case WalkDirection::LEFT:
        {
            goalWorldX = worldX - gameContext->tileSizePx;
            goalWorldY = worldY;
            spriteModel->moveLeft();
            break;
        }
        case WalkDirection::RIGHT:
        {
            // TODO: ONLY SET GOAL IF THE TILE NEXT TO US IS WALKABLE
            goalWorldX = worldX + gameContext->tileSizePx;
            goalWorldY = worldY;
            spriteModel->moveRight();
            break;
        }    
    }
}
