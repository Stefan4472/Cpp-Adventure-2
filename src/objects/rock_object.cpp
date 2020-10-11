#include "rock_object.h"

RockObject::RockObject(double worldX, double worldY) 
    : MapObject(ObjectType::ROCK, worldX, worldY)
{

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
