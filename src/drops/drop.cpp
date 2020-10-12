#include "drop.h"

Drop::Drop(
        GameContext* gameContext,
        std::shared_ptr<Item> item,
        SDL_Rect worldCoords
) {
    this->gameContext = gameContext;
    this->item = item;
    this->worldCoords = worldCoords;
}

std::shared_ptr<Item> Drop::getItem()
{
    return item;
}

void Drop::update(UpdateContext& updateContext)
{

}

void Drop::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        item->getTextureId(),
        worldCoords.x,
        worldCoords.y
    );
}
