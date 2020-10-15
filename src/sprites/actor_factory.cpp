#include "actor_factory.h"

std::shared_ptr<Actor> ActorFactory::createActor(
        GameContext* gameContext,
        SpriteType spriteType,
        SDL_Rect worldCoords
) {
    switch (spriteType)
    {
        case SpriteType::PLAYER:
        {
            return std::make_shared<PlayerActor>(
                gameContext,
                worldCoords
            );
        }
        case SpriteType::FRIENDLY:
        {
            return std::make_shared<NPCActor>(
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