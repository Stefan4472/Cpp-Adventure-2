#ifndef _WANDER_ACTION_H
#define _WANDER_ACTION_H

#include "action.h"
#include "direction.h"


// Walk in random directions for random numbers of tiles
class WanderAction : public Action
{
public:
    WanderAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
    );
    void start();
    bool getIsFinished();
    void update(UpdateContext* updateContext);

private:
    Direction currDirection;
    int tilesLeft;
    // TODO: MAKE THIS A UTILITY GAMEENGINE METHOD
    Direction genRandomDirection();
    int genRandomDistance();
    // void handlePathBlocked();
};
#endif