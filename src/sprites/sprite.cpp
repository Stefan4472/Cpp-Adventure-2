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

void Sprite::giveItem(std::shared_ptr<Item> item)
{
    std::cout << "Got item " << item << std::endl;
    if (inHandItem)
    {
        throw std::runtime_error("Already has item");
    }
    else
    {
        inHandItem = item;
    }
}

void Sprite::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    std::cout << "Sprite responding" << std::endl;
}


