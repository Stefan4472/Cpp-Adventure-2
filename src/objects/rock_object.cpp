#include "rock_object.h"

RockObject::RockObject(SDL_Rect& baseTile) 
    : MapObject(ObjectType::ROCK, baseTile.x + baseTile.w / 2, baseTile.y + baseTile.h / 2)
{
    // TODO: NEED TO GET TEXTURE DIMENSIONS
    int texture_width, texture_height;
    // std::tie(texture_width, texture_height) = 
    // drawWorldX = worldX 
}

bool RockObject::getIsWalkable()
{
    return false;
}

void RockObject::update(UpdateContext* updateContext)
{
    
}

void RockObject::draw(GameRenderer* gameRenderer)
{
    gameRenderer->drawToWorld(
        TextureId::ROCK_OBJECT,
        worldX,
        worldY
    );
}
