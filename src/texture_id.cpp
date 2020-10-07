#include "texture_id.h"

std::string getFilename(TextureId id)
{
    switch (id) 
    {
        case TextureId::SPRITE_FRONT:
        {
            return "sprite-front.png";
        }
        case TextureId::GRASS_TILE:
        {
            return "grass-tile.png";
        }
        case TextureId::DIRT_TILE:
        {
            return "dirt-tile.png";
        }
        case TextureId::SAND_TILE:
        {
            return "sand-tile.png";
        }
        case TextureId::STONE_TILE:
        {
            return "stone-tile.png";
        }
        default:
        {
            throw std::invalid_argument("Unsupported TextureId");
        }
    }
}