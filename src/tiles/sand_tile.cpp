#include "sand_tile.h"

SandTile::SandTile(double worldX, double worldY) 
    : Tile(TileType::SAND, worldX, worldY)
{

}

void SandTile::update(UpdateContext* updateContext)
{

}

void SandTile::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::SAND_TILE,
        worldX,
        worldY
    );
}
