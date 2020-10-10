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
        case TileType::SAND:
        case TileType::DIRT:
        case TileType::STONE:
        {
            return std::make_shared<GrassTile>(
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