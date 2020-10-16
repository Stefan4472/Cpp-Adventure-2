#ifndef _FOLLOW_ACTION_H
#define _FOLLOW_ACTION_H

#include <cmath>
#include "action.h"
#include "direction.h"


// Currently can only follow the player
class FollowAction : public Action
{
public:
    FollowAction(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
    );
    void start();
    bool getIsFinished();
    void update(UpdateContext* updateContext);
};

#endif