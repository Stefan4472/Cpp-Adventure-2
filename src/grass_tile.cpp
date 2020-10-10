#include "grass_tile.h"

GrassTile::GrassTile(double worldX, double worldY) 
    : Tile(TileType::GRASS, worldX, worldY)
{

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
