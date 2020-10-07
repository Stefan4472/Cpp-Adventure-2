#ifndef _TEXTURE_ID_H
#define _TEXTURE_ID_H

#include <string> 

enum class TextureId
{
    SPRITE_FRONT,
    GRASS_TILE
};

std::string getFilename(TextureId id);

#endif