#include "object_factory.h"

std::shared_ptr<MapObject> ObjectFactory::createObject(
        ObjectType objectType, 
        SDL_Rect& baseTile
) {
    switch (objectType)
    {
        case ObjectType::ROCK:
        {
            return std::make_shared<RockObject>(
                baseTile
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