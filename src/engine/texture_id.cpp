#include "texture_id.h"

std::string getFilename(TextureId id)
{
    switch (id) 
    {
        case TextureId::SPRITE_FRONT:
        {
            return "player-front.png";
        }
        case TextureId::SPRITE_BACK:
        {
            return "player-back.png";
        }
        case TextureId::SPRITE_LEFT:
        {
            return "player-left.png";
        }
        case TextureId::SPRITE_RIGHT:
        {
            return "player-right.png";
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
        case TextureId::SPRITE_WALK_UP:
        {
            return "player-walk-up.png";
        }
        case TextureId::SPRITE_WALK_DOWN:
        {
            return "player-walk-down.png";
        }
        case TextureId::SPRITE_WALK_LEFT:
        {
            return "player-walk-left.png";
        }
        case TextureId::SPRITE_WALK_RIGHT:
        {
            return "player-walk-right.png";
        }
        case TextureId::ROCK_OBJECT:
        {
            return "rock.png";
        }
        case TextureId::PICKAXE_ITEM:
        {
            return "pickaxe.png";
        }
        case TextureId::GRAVEL_ITEM:
        {
            return "gravel.png";
        }
        default:
        {
            throw std::invalid_argument("Unsupported TextureId");
        }
    }
}