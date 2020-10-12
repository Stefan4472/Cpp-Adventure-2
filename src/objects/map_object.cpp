#include "map_object.h"

MapObject::MapObject(
        GameContext* gameContext,
        ObjectType objectType, 
        double worldX, 
        double worldY
) {
    this->gameContext = gameContext;
    this->objectType = objectType;
    this->worldX = worldX;
    this->worldY = worldY;
    removeFromGame = false;
}

ObjectType MapObject::getObjectType()
{
    return objectType;
}

bool MapObject::getRemoveFromGame()
{
    return removeFromGame;
}

void MapObject::respondToInteract(
        InteractInterface* interactInterface,
        Sprite* owner, 
        Item* withItem
) {
    std::cout << "MapObject responding" << std::endl;
}
