#include "stone_tile.h"

StoneTile::StoneTile(double worldX, double worldY) 
    : Tile(TileType::STONE, worldX, worldY)
{

}

void StoneTile::update(UpdateContext* updateContext)
{

}

void StoneTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::STONE_TILE,
        worldX,
        worldY
    );
}
