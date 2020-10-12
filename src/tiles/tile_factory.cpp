#include "tile_factory.h"

std::shared_ptr<Tile> TileFactory::createTile(
        GameContext* gameContext,
        TileType tileType, 
        SDL_Rect worldCoords
) {
    // TODO: FOR NOW JUST TESTING OUT WITH GRASS TILE
    switch (tileType)
    {
        case TileType::GRASS:
        {
            return std::make_shared<GrassTile>(
                gameContext,
                worldCoords
            );
        }
        case TileType::SAND:
        {
            return std::make_shared<SandTile>(
                gameContext,
                worldCoords
            );
        }
        case TileType::DIRT:
        {
            return std::make_shared<DirtTile>(
                gameContext,
                worldCoords
            );
        }
        case TileType::STONE:
        {
            return std::make_shared<StoneTile>(
                gameContext,
                worldCoords
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