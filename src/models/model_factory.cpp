#include "model_factory.h"

std::shared_ptr<SpriteModel> ModelFactory::createSpriteModel(
        TextureCache* textureCache,
        SpriteType spriteType
) {
    switch (spriteType)
    {
        case SpriteType::PLAYER:
        {
            // TODO: START ON FRAME 1?
            // WE WANT THE ANIMATION TO START ON FRAME 1, BUT TO LOOP ON FRAME 0.
            auto walk_up_sheet = std::make_shared<Spritesheet>(
                textureCache,
                TextureId::SPRITE_WALK_UP,
                std::vector<int>({100, 100, 100, 100}),
                true
            );
            auto walk_down_sheet = std::make_shared<Spritesheet>(
                textureCache,
                TextureId::SPRITE_WALK_DOWN,
                std::vector<int>({100, 100, 100, 100}),
                true
            );
            auto walk_left_sheet = std::make_shared<Spritesheet>(
                textureCache,
                TextureId::SPRITE_WALK_LEFT,
                std::vector<int>({100, 100, 100, 100}),
                true
            );
            auto walk_right_sheet = std::make_shared<Spritesheet>(
                textureCache,
                TextureId::SPRITE_WALK_RIGHT,
                std::vector<int>({100, 100, 100, 100}),
                true
            );
            return std::make_shared<SpriteModel>(
                TextureId::SPRITE_BACK,
                TextureId::SPRITE_FRONT,
                TextureId::SPRITE_LEFT,
                TextureId::SPRITE_RIGHT,
                walk_up_sheet,
                walk_down_sheet,
                walk_left_sheet,
                walk_right_sheet
            );
        }
        default:
        {
            throw new std::invalid_argument(
                std::string("Unsupported SpriteType ") + 
                std::to_string(static_cast<int>(spriteType))
            );
        }
    }
}