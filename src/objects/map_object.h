#ifndef _MAP_OBJECT_H
#define _MAP_OBJECT_H

#include "object_type.h"
#include "update_context.h"
#include "game_renderer.h"
#include "game_context.h"
#include "sprite.h"
#include "item.h"


class MapObject
{
public:
    MapObject(
        GameContext* gameContext,
        ObjectType objectType, 
        SDL_Rect worldCoords
    );

    ObjectType getObjectType();
    
    virtual bool getIsWalkable() = 0;
    
    virtual void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    ) = 0;
    
    virtual void update(UpdateContext& updateContext) = 0;
    
    virtual void draw(GameRenderer* gameRenderer) = 0;

protected:
    GameContext* gameContext;
    ObjectType objectType;
    SDL_Rect worldCoords;
};

#endif