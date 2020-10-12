#include "sand_tile.h"

SandTile::SandTile(
        GameContext* gameContext, 
        SDL_Rect worldCoords
) : Tile(gameContext, TileType::SAND, worldCoords)
{

}

void SandTile::respondToInteract(
        UpdateContext& updateContext,
        Sprite* owner, 
        Item* withItem
) {

}

void SandTile::update(UpdateContext& updateContext)
{

}

void SandTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::SAND_TILE,
        worldCoords.x,
        worldCoords.y
    );
}
