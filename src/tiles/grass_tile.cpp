#include "grass_tile.h"

GrassTile::GrassTile(double worldX, double worldY) 
    : Tile(TileType::GRASS, worldX, worldY)
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
        // TODO: PROVIDE + USE GAMECONTEXT
        int tile_x, tile_y;
        tile_x = static_cast<int>(worldX / TextureCache::TILE_SIZE_PX);
        tile_y = static_cast<int>(worldY / TextureCache::TILE_SIZE_PX);
        updateContext.requestCreateObject(
            ObjectType::ROCK,
            tile_x,
            tile_y
        );

        updateContext.requestReplaceTile(
            TileType::SAND,
            tile_x,
            tile_y
        );
    }
}

void GrassTile::update(UpdateContext* updateContext)
{

}

void GrassTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::GRASS_TILE,
        worldX,
        worldY
    );
}
