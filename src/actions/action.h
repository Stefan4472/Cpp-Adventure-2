#ifndef _ACTION_H
#define _ACTION_H

#include "sprite.h"

// An action is done onto a `Sprite`, and managed by an `Actor`.
// I.e., the Actor applies an Action to a Sprite.
class Action
{
public:
    Action(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
    );
    virtual void start() = 0;
    virtual bool getIsFinished() = 0;
    virtual void update(UpdateContext* updateContext) = 0;

protected:
    GameContext* gameContext;
    std::shared_ptr<Sprite> sprite;
};

#endif