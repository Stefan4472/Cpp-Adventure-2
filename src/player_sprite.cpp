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

    walkDownSpritesheet->start();
}

void PlayerSprite::giveInput(EventId eventId)
{

}

void PlayerSprite::moveUp()
{
    if (tileY > 1)
    {
        tileY -= 1;
        updateCoords();
    }
}

void PlayerSprite::moveDown()
{
    if (tileY < gameContext->map->numRows)
    {
        tileY += 1;
        updateCoords();
    }
}

void PlayerSprite::moveLeft()
{
    if (tileX > 0)
    {
        tileX -= 1;
        updateCoords();
    }
}

void PlayerSprite::moveRight()
{
    if (tileX < gameContext->map->numCols - 1)
    {
        tileX += 1;
        updateCoords();
    }
}

void PlayerSprite::updateCoords()
{
    worldX = tileX * gameContext->tileSizePx;
    worldY = tileY * gameContext->tileSizePx;
    // std::cout << worldX << ", " << worldY << std::endl;
}

void PlayerSprite::update(UpdateContext* updateContext)
{
    walkDownSpritesheet->update(
        updateContext->msSincePrevUpdate
    );
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