#ifndef _ROCK_OBJECT_H
#define _ROCK_OBJECT_H

#include "map_object.h"

class RockObject : public MapObject
{
public:
    RockObject(
        GameContext* gameContext, 
        SDL_Rect worldCoords
    );

    bool getIsWalkable();
    
    void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    );
    
    void update(UpdateContext& updateContext);

    void draw(GameRenderer* gameRenderer);

private:
    // Draw coordinates
    double drawWorldX, drawWorldY;
};

#endif