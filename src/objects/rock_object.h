#ifndef _ROCK_OBJECT_H
#define _ROCK_OBJECT_H

#include "map_object.h"

class RockObject : public MapObject
{
public:
    RockObject(SDL_Rect& baseTile);
    bool getIsWalkable();
    void update(UpdateContext* updateContext);
    void draw(GameRenderer* gameRenderer);

private:
    // Draw coordinates, derived from world coordinates
    double drawWorldX, drawWorldY;
};

#endif