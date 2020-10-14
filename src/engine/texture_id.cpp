#include "texture_id.h"

boost::filesystem::path getRelPath(TextureId id)
{
    // TODO: NOTE: THESE PATHS MIGHT NOT BE CROSS-PLATFORM DUE TO THE HARD-CODED '/' SEPARATOR
    switch (id) 
    {
        case TextureId::SPRITE_FRONT:
        {
            return boost::filesystem::path("sprites/player/front.png");
        }
        case TextureId::SPRITE_BACK:
        {
            return boost::filesystem::path("sprites/player/back.png");
        }
        case TextureId::SPRITE_LEFT:
        {
            return boost::filesystem::path("sprites/player/left.png");
        }
        case TextureId::SPRITE_RIGHT:
        {
            return boost::filesystem::path("sprites/player/right.png");
        }
        case TextureId::GRASS_TILE:
        {
            return boost::filesystem::path("tiles/grass.png");
        }
        case TextureId::DIRT_TILE:
        {
            return boost::filesystem::path("tiles/dirt.png");
        }
        case TextureId::SAND_TILE:
        {
            return boost::filesystem::path("tiles/sand.png");
        }
        case TextureId::STONE_TILE:
        {
            return boost::filesystem::path("tiles/stone.png");
        }
        case TextureId::SPRITE_WALK_UP:
        {
            return boost::filesystem::path("sprites/player/walk-up.png");
        }
        case TextureId::SPRITE_WALK_DOWN:
        {
            return boost::filesystem::path("sprites/player/walk-down.png");
        }
        case TextureId::SPRITE_WALK_LEFT:
        {
            return boost::filesystem::path("sprites/player/walk-left.png");
        }
        case TextureId::SPRITE_WALK_RIGHT:
        {
            return boost::filesystem::path("sprites/player/walk-right.png");
        }
        case TextureId::ROCK_OBJECT:
        {
            return boost::filesystem::path("objects/rock.png");
        }
        case TextureId::PICKAXE_ITEM:
        {
            return boost::filesystem::path("items/pickaxe.png");
        }
        case TextureId::GRAVEL_ITEM:
        {
            return boost::filesystem::path("items/gravel.png");
        }
        default:
        {
            throw std::invalid_argument("Unsupported TextureId");
        }
    }
}