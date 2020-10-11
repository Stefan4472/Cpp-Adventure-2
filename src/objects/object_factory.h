#ifndef _OBJECT_FACTORY_H
#define _OBJECT_FACTORY_H

#include <memory>
#include "object_type.h"
#include "map_object.h"
#include "rock_object.h"


class ObjectFactory
{
public:
    static std::shared_ptr<MapObject> createObject(
        GameContext* gameContext, 
        ObjectType objectType, 
        SDL_Rect& baseTile
    );
};

#endif