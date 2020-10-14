#ifndef _TEXTURE_ID_H
#define _TEXTURE_ID_H

#include <boost/filesystem.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept> 

// NOTE: each texture must have a filepath defined in `texture_id.cpp`
// TODO: IMPLEMENT A TEXTURE ATLAS
enum class TextureId
{
    // Tiles
    GRASS_TILE,
    DIRT_TILE,
    SAND_TILE,
    STONE_TILE,
    // MapObjects
    ROCK_OBJECT,
    // Items
    PICKAXE_ITEM,
    GRAVEL_ITEM,
    // Player sprite
    SPRITE_FRONT,
    SPRITE_BACK,
    SPRITE_LEFT,
    SPRITE_RIGHT,
    SPRITE_WALK_UP,
    SPRITE_WALK_DOWN,
    SPRITE_WALK_LEFT,
    SPRITE_WALK_RIGHT,
    // Friendly sprite
    FRIENDLY_FRONT,
    FRIENDLY_BACK,
    FRIENDLY_LEFT,
    FRIENDLY_RIGHT,
    FRIENDLY_WALK_UP,
    FRIENDLY_WALK_DOWN,
    FRIENDLY_WALK_LEFT,
    FRIENDLY_WALK_RIGHT
};

boost::filesystem::path getRelPath(TextureId id);

#endif