#include "grass_tile.h"

GrassTile::GrassTile(
        GameContext* gameContext, 
        SDL_Rect worldCoords
) : Tile(gameContext, TileType::GRASS, worldCoords)
{

}

void GrassTile::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    // TODO: FOR TEMPORARY DEVELOPMENT/TESTING PURPOSES ONLY
    if (withItem->getItemType() == ItemType::PICKAXE)
    {
        int tile_x, tile_y;
        std::tie(tile_x, tile_y) = gameContext->engine->resolveTile(
            worldCoords.x,
            worldCoords.y
        );

        updateContext.requestReplaceTile(
            TileType::SAND,
            tile_x,
            tile_y
        );
        
        updateContext.requestCreateObject(
            ObjectType::ROCK,
            tile_x,
            tile_y
        );
    }
}

void GrassTile::update(UpdateContext& updateContext)
{

}

void GrassTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::GRASS_TILE,
        worldCoords.x,
        worldCoords.y
    );
}
