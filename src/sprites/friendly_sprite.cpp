#include "friendly_sprite.h"

FriendlySprite::FriendlySprite(
    GameContext* gameContext, 
    SDL_Rect baseTile
) : Sprite(gameContext, SpriteType::FRIENDLY, baseTile.x + baseTile.w / 2, baseTile.y + baseTile.h - 1)
{

}

void FriendlySprite::update(UpdateContext* updateContext)
{

}

void FriendlySprite::draw(GameRenderer* renderer)
{
    int tex_width, tex_height;
    std::tie(tex_width, tex_height) = gameContext->textureCache->getDimensions(
        TextureId::FRIENDLY_FRONT
    );
    renderer->drawToWorld(
        TextureId::FRIENDLY_FRONT,
        worldX - tex_width / 2,
        worldY - tex_height
    );
}
