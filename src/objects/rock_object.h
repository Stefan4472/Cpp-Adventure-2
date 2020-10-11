#ifndef _ROCK_OBJECT_H
#define _ROCK_OBJECT_H

#include "map_object.h"

class RockObject : public MapObject
{
public:
    RockObject(double worldX, double worldY);
    bool getIsWalkable();
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* gameRenderer);
};

#endif