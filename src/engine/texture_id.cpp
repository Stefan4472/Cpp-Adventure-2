#include "texture_id.h"


// ADD NEW TEXTURES HERE:
// TODO: NOTE: THESE PATHS MIGHT NOT BE CROSS-PLATFORM DUE TO THE HARD-CODED '/' SEPARATOR
const std::unordered_map<TextureId, boost::filesystem::path> TEX_TO_PATH_MAPPINGS = 
{
    {TextureId::SPRITE_FRONT, boost::filesystem::path("sprites/player/front.png")},
    {TextureId::SPRITE_BACK, boost::filesystem::path("sprites/player/back.png")},
    {TextureId::SPRITE_LEFT, boost::filesystem::path("sprites/player/left.png")},
    {TextureId::SPRITE_RIGHT, boost::filesystem::path("sprites/player/right.png")},
    {TextureId::GRASS_TILE, boost::filesystem::path("tiles/grass.png")},
    {TextureId::DIRT_TILE, boost::filesystem::path("tiles/dirt.png")},
    {TextureId::SAND_TILE, boost::filesystem::path("tiles/sand.png")},
    {TextureId::STONE_TILE, boost::filesystem::path("tiles/stone.png")},
    {TextureId::SPRITE_WALK_UP, boost::filesystem::path("sprites/player/walk-up.png")},
    {TextureId::SPRITE_WALK_DOWN, boost::filesystem::path("sprites/player/walk-down.png")},
    {TextureId::SPRITE_WALK_LEFT, boost::filesystem::path("sprites/player/walk-left.png")},
    {TextureId::SPRITE_WALK_RIGHT, boost::filesystem::path("sprites/player/walk-right.png")},
    {TextureId::ROCK_OBJECT, boost::filesystem::path("objects/rock.png")},
    {TextureId::PICKAXE_ITEM, boost::filesystem::path("items/pickaxe.png")},
    {TextureId::GRAVEL_ITEM, boost::filesystem::path("items/gravel.png")}
};

boost::filesystem::path getRelPath(TextureId id)
{
    auto it = TEX_TO_PATH_MAPPINGS.find(id);
    if (it == TEX_TO_PATH_MAPPINGS.end())
    {
        throw std::invalid_argument(
            "Unsupported TextureId/missing filepath definition"
        );
    }
    else
    {
        return it->second;
    }
}