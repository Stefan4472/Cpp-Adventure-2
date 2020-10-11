#include "sprite.h"

Sprite::Sprite(
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType, 
        double worldX, 
        double worldY
) {
    this->gameContext = gameContext;
    this->spriteType = spriteType;
    this->worldX = worldX;
    this->worldY = worldY;
}

std::pair<double, double> Sprite::getWorldCoords()
{
    return std::make_pair(
        worldX,
        worldY
    );
}

