#ifndef _TEXTURE_ID_H
#define _TEXTURE_ID_H

#include <string>
#include <stdexcept> 

enum class TextureId
{
    SPRITE_FRONT,
    GRASS_TILE,
    DIRT_TILE,
    SAND_TILE,
    STONE_TILE
};

std::string getFilename(TextureId id);

#endif