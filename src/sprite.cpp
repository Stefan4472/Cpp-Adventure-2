#include "sprite.h"

Sprite::Sprite(GameContext* gameContext, SpriteType spriteType)
{
    this->gameContext = gameContext;
    this->spriteType = spriteType;
}

Sprite::Sprite(GameContext* gameContext, SpriteType spriteType, double worldX, double worldY)
{
    this->gameContext = gameContext;
    this->spriteType = spriteType;
    this->worldX = worldX;
    this->worldY = worldY;
    this->tileX = this->worldX / gameContext->tileSizePx;
    this->tileY = this->worldY / gameContext->tileSizePx;
}
