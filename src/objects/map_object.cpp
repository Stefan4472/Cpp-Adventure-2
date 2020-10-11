#include "map_object.h"

MapObject::MapObject(ObjectType objectType, double worldX, double worldY)
{
    this->objectType = objectType;
    this->worldX = worldX;
    this->worldY = worldY;
}

ObjectType MapObject::getTileType()
{
    return objectType;
}