#ifndef _IDLE_ACTION_H
#define _IDLE_ACTION_H

#include "action.h"
#include "direction.h"


// Stay on one tile, look around in random directions
class IdleAction : public Action
{
public:
    IdleAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
    );
    void start();
    bool getIsFinished();
    void update(UpdateContext* updateContext);
    // How often to potentially change direction.
    // (50% chance of changing direction after each period)
    const int CHANGE_DIR_TIME_MS = 4000;

private:
    int msSinceLastChange = 0;

    Direction getRandomDirection();
};

#endif