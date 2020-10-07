#include "tile_type.h"

TextureId getTileTextureId(TileType tileType)
{
    switch (tileType)
    {
        case TileType::GRASS:
        {
            return TextureId::GRASS_TILE;
        }
        case TileType::DIRT:
        {
            return TextureId::DIRT_TILE;
        }
        case TileType::SAND:
        {
            return TextureId::SAND_TILE;
        }
        case TileType::STONE:
        {
            return TextureId::STONE_TILE;
        }
        default:
        {
            throw std::invalid_argument("Unsupported TileType");
        }
    }
}