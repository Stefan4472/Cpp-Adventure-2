#ifndef _TEXTURE_ID_H
#define _TEXTURE_ID_H

#include <boost/filesystem.hpp>
#include <string>
#include <stdexcept> 

enum class TextureId
{
    SPRITE_FRONT,
    SPRITE_BACK,
    SPRITE_LEFT,
    SPRITE_RIGHT,
    GRASS_TILE,
    DIRT_TILE,
    SAND_TILE,
    STONE_TILE,
    SPRITE_WALK_UP,
    SPRITE_WALK_DOWN,
    SPRITE_WALK_LEFT,
    SPRITE_WALK_RIGHT,
    ROCK_OBJECT,
    PICKAXE_ITEM,
    GRAVEL_ITEM
};

boost::filesystem::path getRelPath(TextureId id);

#endif