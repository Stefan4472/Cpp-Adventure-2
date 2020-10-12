#include "stone_tile.h"

StoneTile::StoneTile(
        GameContext* gameContext, 
        SDL_Rect worldCoords
) : Tile(gameContext, TileType::STONE, worldCoords)
{

}

void StoneTile::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {
    
}

void StoneTile::update(UpdateContext& updateContext)
{

}

void StoneTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::STONE_TILE,
        worldCoords.x,
        worldCoords.y
    );
}
