#ifndef _MODEL_FACTORY_H
#define _MODEL_FACTORY_H

#include <memory>
#include "sprite_model.h"
#include "sprite_type.h"
#include "texture_cache.h"


// Creates and returns a new `SpriteModel` for the specified
// SpriteType.
class ModelFactory
{
public:
    static std::shared_ptr<SpriteModel> createSpriteModel(
        TextureCache* textureCache,
        SpriteType spriteType
    );
};

#endif