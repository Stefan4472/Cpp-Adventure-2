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
        std::shared_ptr<GameContext> gameContext, 
        SpriteType spriteType, 
        double worldX, 
        double worldY
    );

    // Item in hand (may be NULL)
    // TODO: MAKE PRIVATE. CURRENTLY PUBLIC FOR TESTING/DEV
    std::shared_ptr<Item> inHandItem;

    std::pair<double, double> getWorldCoords();

    void giveItem(std::shared_ptr<Item> item);

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
    std::shared_ptr<GameContext> gameContext;
    SpriteType spriteType;
    // TODO: DIFFERENTIATE BETWEEN WORLD COORDINATES AND DRAW COORDINATES
    // World coordinates
    double worldX, worldY;
};

#endif