#include "sprite_factory.h"

std::shared_ptr<Sprite> SpriteFactory::createSprite(
        GameContext* gameContext,
        SpriteType spriteType,
        SDL_Rect worldCoords
) {
    switch (spriteType)
    {
        case SpriteType::PLAYER:
        {
            return std::make_shared<PlayerSprite>(
                gameContext,
                worldCoords
            );
        }
        case SpriteType::FRIENDLY:
        {
            return std::make_shared<FriendlySprite>(
                gameContext,
                worldCoords
            );
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported spriteType ") + 
                std::to_string(static_cast<int>(spriteType))
            );
        }
    }
}