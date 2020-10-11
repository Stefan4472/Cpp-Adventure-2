#include "rock_object.h"

RockObject::RockObject(GameContext* gameContext, SDL_Rect& baseTile) 
    : MapObject(gameContext, ObjectType::ROCK, baseTile.x + baseTile.w / 2, baseTile.y + baseTile.h / 2)
{
    // Set our draw coordinates to center the image in the tile.
    int texture_width, texture_height;
    std::tie(texture_width, texture_height) = 
        gameContext->textureCache->getDimensions(TextureId::ROCK_OBJECT);
    drawWorldX = worldX - texture_width / 2;
    drawWorldY = worldY - texture_height / 2; 
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
        drawWorldX,
        drawWorldY
    );
}
