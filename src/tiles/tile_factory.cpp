#include "tile_factory.h"

std::shared_ptr<Tile> TileFactory::createTile(
        TileType tileType, 
        double worldX, 
        double worldY
) {
    // TODO: FOR NOW JUST TESTING OUT WITH GRASS TILE
    switch (tileType)
    {
        case TileType::GRASS:
        {
            return std::make_shared<GrassTile>(
                worldX, 
                worldY
            );
        }
        case TileType::SAND:
        {
            return std::make_shared<SandTile>(
                worldX, 
                worldY
            );
        }
        case TileType::DIRT:
        {
            return std::make_shared<DirtTile>(
                worldX, 
                worldY
            );
        }
        case TileType::STONE:
        {
            return std::make_shared<StoneTile>(
                worldX, 
                worldY
            );
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported tileType ") + 
                std::to_string(static_cast<int>(tileType))
            );
        }
    }
}