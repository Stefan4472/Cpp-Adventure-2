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
    STONE_TILE,
    SPRITE_WALK_UP,
    SPRITE_WALK_DOWN,
    SPRITE_WALK_LEFT,
    SPRITE_WALK_RIGHT,
    ROCK_OBJECT,
    PICKAXE_ITEM,
    GRAVEL_ITEM
};

// TODO: RETURN RELATIVE PATH. THAT WAY WE CAN ORGANIZE ART INTO SUB-DIRECTORIES (E.G. 'TILES', 'SPRITES', ETC.)
std::string getFilename(TextureId id);

#endif