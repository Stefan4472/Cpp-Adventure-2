#include "action.h"

Action::Action(std::shared_ptr<TestSprite> sprite)
{
    this->sprite = sprite;
}

void Action::start()
{
    sprite->walkDown(TextureCache::TILE_SIZE_PX * 10);
}

bool Action::getIsFinished()
{
    return !sprite->getIsWalking();
}

void Action::update(UpdateContext* updateContext)
{

}

