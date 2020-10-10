#include "dirt_tile.h"

DirtTile::DirtTile(double worldX, double worldY) 
    : Tile(TileType::DIRT, worldX, worldY)
{

}

void DirtTile::update(UpdateContext* updateContext)
{

}

void DirtTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::DIRT_TILE,
        worldX,
        worldY
    );
}
