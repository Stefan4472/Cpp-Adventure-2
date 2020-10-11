#ifndef _MAP_OBJECT_H
#define _MAP_OBJECT_H

#include "object_type.h"
#include "update_context.h"
#include "game_renderer.h"


class MapObject
{
public:
    MapObject(ObjectType objectType, double worldX, double worldY);
    ObjectType getTileType();
    
    virtual bool getIsWalkable() = 0;
    virtual void update(UpdateContext* updateContext) = 0;
    virtual void draw(GameRenderer* gameRenderer) = 0;

protected:
    ObjectType objectType;
    double worldX, worldY;
};

#endif