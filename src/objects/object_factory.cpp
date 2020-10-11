#include "object_factory.h"

std::shared_ptr<MapObject> ObjectFactory::createObject(
        ObjectType objectType, 
        double worldX, 
        double worldY
) {
    switch (objectType)
    {
        case ObjectType::ROCK:
        {
            return std::make_shared<RockObject>(
                worldX, 
                worldY
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