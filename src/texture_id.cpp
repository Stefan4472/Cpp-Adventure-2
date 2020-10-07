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
        default:
        {
            // TODO: THROW EXCEPTION
        }
    }
}