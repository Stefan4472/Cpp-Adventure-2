#ifndef _ACTION_H
#define _ACTION_H

#include "sprite.h"

// An action is done onto a `Sprite`, and managed by an `Actor`.
// I.e., the Actor applies an Action to a Sprite.
class Action
{
// TODO: THIS WILL BE MADE INTO A BASE CLASS. FOR EARLY DEVELOPMENT,
// WE WILL HAVE IT MAKE THE SPRITE WALK FIVE TILES AHEAD OF IT
public:
    Action(std::shared_ptr<Sprite> sprite);
    void start();
    bool getIsFinished();
    void update(UpdateContext* updateContext);

private:
    std::shared_ptr<Sprite> sprite;
};

#endif