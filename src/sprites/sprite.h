#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>
#include <memory>
#include "game_context.h"
#include "update_context.h"
#include "game_renderer.h"
#include "sprite_type.h"
#include "item.h"

class Sprite
{
public:
    Sprite(
        GameContext* gameContext, 
        SpriteType spriteType,
        double worldX, 
        double worldY
    );

    SpriteType getSpriteType();

    std::pair<double, double> getWorldCoords();

    // Gives the Sprite the specified Item. Returns
    // whether the Sprite accepted the item.
    // TODO: MAYBE ONLY THE PLAYER SHOULD HAVE THIS?
    virtual bool giveItem(std::shared_ptr<Item> item);

    /* Abstract methods */
    virtual void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    );
    // Update
    virtual void update(UpdateContext* updateContext) = 0;
    // Draw self onto provided renderer
    virtual void draw(GameRenderer* renderer) = 0;

protected:
    GameContext* gameContext;
    SpriteType spriteType;
    // TODO: DIFFERENTIATE BETWEEN WORLD COORDINATES AND DRAW COORDINATES
    // World coordinates
    double worldX, worldY;
};

#endif