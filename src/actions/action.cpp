#include "action.h"

Action::Action(
        GameContext* gameContext,
        std::shared_ptr<Sprite> sprite
) {
    this->gameContext = gameContext;
    this->sprite = sprite;
}