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

    walkUpSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_UP,
        std::vector<int>({200, 200, 200, 200}),
        true
    );
    walkDownSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_DOWN,
        std::vector<int>({200, 200, 200, 200}),
        true
    );
    walkLeftSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_LEFT,
        std::vector<int>({200, 200, 200, 200}),
        true
    );
    walkRightSpritesheet = std::make_shared<Spritesheet>(
        gameContext->textureCache.get(),
        TextureId::SPRITE_WALK_RIGHT,
        std::vector<int>({200, 200, 200, 200}),
        true
    );
    spriteModel = std::make_shared<SpriteModel>(
        TextureId::SPRITE_WALK_UP,
        walkUpSpritesheet,
        walkDownSpritesheet,
        walkLeftSpritesheet,
        walkRightSpritesheet
    );

    walkPxPerMs = gameContext->tileSizePx * 1.0 / TILE_WALK_TIME_MS;
    currWalkCommand = WalkDirection::NONE;
    goalWorldX = worldX;
    goalWorldY = worldY;

    // Start walking animation (testing purposes)
    walkDownSpritesheet->start();
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
    walkDownSpritesheet->update(
        updateContext->msSincePrevUpdate
    );

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
}

void PlayerSprite::draw(SDL_Renderer* renderer)
{
    SDL_Rect dest_rect = {
        static_cast<int>(worldX),
        static_cast<int>(worldY - textureHeight),
        textureWidth,
        textureHeight
    };
    // SDL_RenderCopy(
    //     renderer, 
    //     gameContext->textureCache->getTexture(TextureId::SPRITE_FRONT), 
    //     NULL, 
    //     &dest_rect
    // );
    SDL_Rect src_rect = walkDownSpritesheet->getCurrentFrameSrc();
    SDL_RenderCopy(
        renderer,
        gameContext->textureCache->getTexture(walkDownSpritesheet->getTextureID()),
        &src_rect,
        &dest_rect
    );
}

void PlayerSprite::updateWalkCommand()
{
    currWalkCommand = inputHandler.getNextWalkCommand();
    switch (currWalkCommand)
    {
        case WalkDirection::NONE:
        {
            break;
        }
        case WalkDirection::UP:
        {
            goalWorldX = worldX;
            goalWorldY = worldY - gameContext->tileSizePx;
            break;
        }
        case WalkDirection::DOWN:
        {
            goalWorldX = worldX;
            goalWorldY = worldY + gameContext->tileSizePx;
            break;
        }
        case WalkDirection::LEFT:
        {
            goalWorldX = worldX - gameContext->tileSizePx;
            goalWorldY = worldY;
            break;
        }
        case WalkDirection::RIGHT:
        {
            goalWorldX = worldX + gameContext->tileSizePx;
            goalWorldY = worldY;
            break;
        }    
    }
}
