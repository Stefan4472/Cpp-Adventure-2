#ifndef _ACTOR_H
#define _ACTOR_H

#include "game_context.h"
#include "sprite.h"
#include "model_factory.h"

// Higher-level of logic that controls a Sprite.
class Actor
{
public:
    Actor(
        GameContext* gameContext,
        SpriteType spriteType,
        SDL_Rect worldCoords
    );

    std::shared_ptr<Sprite> getSprite();

    std::pair<double, double> getWorldCoords();

    // TODO: MOVE SOME OF THESE TO `SPRITE`?
    // Get tile coordinates that the sprite is on
    std::pair<int, int> getTileCoords();

    // Get coordinates of the tile the sprite is currently facing
    std::pair<int, int> getFacedTile();

    // Attempts to gives the Actor the specified Item. 
    // Returns whether the Actor accepted the item.
    virtual bool giveItem(
        std::shared_ptr<Item> item
    ) = 0;

    // Responds to an interaction with `owner`, that used `withItem`
    virtual void respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
    ) = 0;

    // TODO: `RESPONDTOBLOCKED()`, CALLED WHEN SPRITE ATTEMPTS TO MOVE ONTO A NON-WALKABLE TILE

    // Update
    virtual void update(UpdateContext* updateContext) = 0;

    // Draw self onto provided renderer
    virtual void draw(GameRenderer* renderer) = 0;

protected:
    GameContext* gameContext;
    std::shared_ptr<Sprite> sprite;
};
#endif