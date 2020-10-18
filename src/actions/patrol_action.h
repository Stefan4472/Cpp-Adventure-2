#ifndef _PATROL_ACTION_H
#define _PATROL_ACTION_H

#include "action.h"
#include "direction.h"


// Simple development action, just walks five blocks down, then five blocks up.
// Does not check that the tile it is on is walkable
class PatrolAction : public Action
{
public:
    PatrolAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
    );
    void start();
    bool getIsFinished();
    void update(UpdateContext* updateContext);

private:
    Direction currDirection;
    int tilesLeft;
};

#endif