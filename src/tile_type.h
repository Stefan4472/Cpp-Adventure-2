#ifndef _TILE_TYPE_H
#define _TILE_TYPE_H

#include "texture_id.h"

enum class TileType 
{
    GRASS,
    SAND,
    DIRT,
    STONE
};

// Map TileType to TextureId
TextureId getTileTextureId(TileType tileType);

#endif