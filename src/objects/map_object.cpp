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
}

ObjectType MapObject::getTileType()
{
    return objectType;
}

void MapObject::respondToInteract(
        InteractInterface* interactInterface,
        Sprite* owner, 
        Item* withItem
) {
    std::cout << "MapObject responding" << std::endl;
}
