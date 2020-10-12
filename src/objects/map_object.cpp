#include "map_object.h"

MapObject::MapObject(
        GameContext* gameContext,
        ObjectType objectType, 
        SDL_Rect worldCoords
) {
    this->gameContext = gameContext;
    this->objectType = objectType;
    this->worldCoords = worldCoords;
}

ObjectType MapObject::getObjectType()
{
    return objectType;
}
