#ifndef _DROP_H
#define _DROP_H

#include <SDL2/SDL.h>
#include <memory>
#include "item.h"
#include "game_context.h"
#include "update_context.h"
#include "game_renderer.h"


// A "Drop" is an item/bunch of items (all of the same type)
// that is visible on the Map and can be picked up
// NOTE: TODO: CURRENTLY, A DROP CONTAINS A SINGLE ITEM, FOR SIMPLICITY
class Drop
{
public:
    Drop(
        GameContext* gameContext,
        std::shared_ptr<Item> item,
        SDL_Rect worldCoords
    );

    std::shared_ptr<Item> getItem();
    void update(UpdateContext& updateContext);
    void draw(GameRenderer* gameRenderer);

private:
    GameContext* gameContext;
    std::shared_ptr<Item> item;
    SDL_Rect worldCoords;
};

#endif