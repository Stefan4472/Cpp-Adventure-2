#include "sprite.h"

Sprite::Sprite(
        GameContext* gameContext, 
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

bool Sprite::giveItem(std::shared_ptr<Item> item)
{
    return false;
}

void Sprite::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    std::cout << "Sprite responding" << std::endl;
}


