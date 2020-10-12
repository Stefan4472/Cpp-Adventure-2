#include "dirt_tile.h"

DirtTile::DirtTile(
        GameContext* gameContext, 
        SDL_Rect worldCoords
) : Tile(gameContext, TileType::DIRT, worldCoords)
{

}

void DirtTile::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {

}

void DirtTile::update(UpdateContext& updateContext)
{
    
}

void DirtTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::DIRT_TILE,
        worldCoords.x,
        worldCoords.y
    );
}
