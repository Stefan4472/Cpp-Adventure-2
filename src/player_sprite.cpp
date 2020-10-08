#include "player_sprite.h"

PlayerSprite::PlayerSprite(GameContext* gameContext, SpriteType spriteType, double worldX, double worldY) :
    Sprite(gameContext, SpriteType::PLAYER, worldX, worldY)
{
    spriteImage = gameContext->textureCache->getTexture(TextureId::SPRITE_FRONT);
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
}

void PlayerSprite::draw(SDL_Surface* surface)
{
    // Draw sprite image.
    SDL_Rect src_rect, dest_rect;

    src_rect.w = spriteImage->w;
    src_rect.h = spriteImage->h;

    // Make the image bottom line up with the tile the sprite is on.
    dest_rect.x = worldX;
    dest_rect.y = worldY - spriteImage->h;

    SDL_BlitSurface(spriteImage, &src_rect, surface, &dest_rect);
}