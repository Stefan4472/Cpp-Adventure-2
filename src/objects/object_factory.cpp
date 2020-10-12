#include "object_factory.h"

std::shared_ptr<MapObject> ObjectFactory::createObject(
        GameContext* gameContext, 
        ObjectType objectType, 
        SDL_Rect worldCoords
) {
    switch (objectType)
    {
        case ObjectType::ROCK:
        {
            return std::make_shared<RockObject>(
                gameContext,
                worldCoords
            );
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported objectType ") + 
                std::to_string(static_cast<int>(objectType))
            );
        }
    }
}