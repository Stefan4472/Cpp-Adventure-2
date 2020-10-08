#include "player_sprite.h"

PlayerSprite::PlayerSprite(GameContext* gameContext, SpriteType spriteType, double worldX, double worldY) :
    Sprite(gameContext, SpriteType::PLAYER, worldX, worldY)
{
    spriteImage = gameContext->textureCache->getTexture(TextureId::SPRITE_FRONT);
}

void PlayerSprite::draw(SDL_Surface* surface)
{
    // Draw sprite image.
    SDL_Rect src_rect, dest_rect;

    src_rect.w = spriteImage->w;
    src_rect.h = spriteImage->h;

    // Make the image bottom line up with the tile the sprite is on.
    // TODO: USE OUR WORLD_X, WORLD_Y COORDINATES
    dest_rect.x = tileX * gameContext->tileSizePx;
    dest_rect.y = tileY * gameContext->tileSizePx - spriteImage->h;

    SDL_BlitSurface(spriteImage, &src_rect, surface, &dest_rect);
}