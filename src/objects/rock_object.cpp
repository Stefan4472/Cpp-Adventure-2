#include "rock_object.h"

RockObject::RockObject(
        GameContext* gameContext, 
        SDL_Rect worldCoords
) : MapObject(gameContext, ObjectType::ROCK, worldCoords)
{
    // Set our draw coordinates to center the image in the tile.
    int texture_width, texture_height;
    std::tie(texture_width, texture_height) = 
        gameContext->textureCache->getDimensions(TextureId::ROCK_OBJECT);
    drawWorldX = worldCoords.x + worldCoords.w / 2 - texture_width / 2;
    drawWorldY = worldCoords.y + worldCoords.h / 2- texture_height / 2; 
}

bool RockObject::getIsWalkable()
{
    return false;
}

void RockObject::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    // Destroy instantly if interacted with Pickaxe
    if (withItem->getItemType() == ItemType::PICKAXE)
    {
        int tile_x, tile_y;
        std::tie(tile_x, tile_y) = gameContext->engine->resolveTile(
            worldCoords.x,
            worldCoords.y
        );
        // Destroy ourselves
        updateContext.requestDestroyObject(
            tile_x,
            tile_y
        );
        // Create drop
        updateContext.requestCreateDrop(
            ItemType::GRAVEL,
            1,
            tile_x,
            tile_y
        );
    }
}

void RockObject::update(UpdateContext& updateContext)
{
    
}

void RockObject::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::ROCK_OBJECT,
        drawWorldX,
        drawWorldY
    );
}
