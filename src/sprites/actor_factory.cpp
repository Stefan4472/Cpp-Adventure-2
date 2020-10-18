#include "actor_factory.h"

std::shared_ptr<Actor> ActorFactory::createActor(
        GameContext* gameContext,
        SpriteType spriteType,
        int spriteId,
        SDL_Rect worldCoords
) {
    switch (spriteType)
    {
        case SpriteType::PLAYER:
        {
            return std::make_shared<PlayerActor>(
                gameContext,
                spriteId,
                worldCoords
            );
        }
        case SpriteType::PATROLLER:
        case SpriteType::FOLLOWER:
        case SpriteType::WANDERER:
        case SpriteType::IDLER:
        {
            return std::make_shared<NPCActor>(
                gameContext,
                spriteType,
                spriteId,
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