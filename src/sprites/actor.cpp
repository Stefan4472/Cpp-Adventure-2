#include "actor.h"

Actor::Actor(
    GameContext* gameContext,
    SpriteType spriteType,
    int spriteID,
    SDL_Rect worldCoords
) {
    this->gameContext = gameContext;

    auto model = ModelFactory::createSpriteModel(
        gameContext->textureCache.get(),
        spriteType
    );

    // Center world coordinates in the tile
    double world_x = worldCoords.x + worldCoords.w / 2;
    double world_y = worldCoords.y + worldCoords.h - 1;

    sprite = std::make_shared<Sprite>(
        gameContext,
        spriteType, 
        spriteID,
        model,
        world_x, 
        world_y
    );
}

std::shared_ptr<Sprite> Actor::getSprite()
{
    return sprite;
}

std::pair<double, double> Actor::getWorldCoords()
{
    return sprite->getWorldCoords();
}

std::pair<int, int> Actor::getTileCoords()
{
    return sprite->getTileCoords();
}

std::pair<int, int> Actor::getFacedTile()
{
    // Get current tile
    int curr_tile_x, curr_tile_y;
    std::tie(curr_tile_x, curr_tile_y) = getTileCoords();

    // Determine the tile to interact with.
    switch (sprite->getFacingDirection())
    {
        case Direction::UP:
        {
            return std::make_pair(
                curr_tile_x,
                curr_tile_y - 1
            );
        }
        case Direction::DOWN:
        {
            return std::make_pair(
                curr_tile_x,
                curr_tile_y + 1
            );
        }
        case Direction::LEFT:
        {
            return std::make_pair(
                curr_tile_x - 1,
                curr_tile_y
            );
        }
        case Direction::RIGHT:
        {
            return std::make_pair(
                curr_tile_x + 1,
                curr_tile_y
            );
        }
        default:
        {
            throw std::runtime_error(
                "Sprite direction is uninitialized"
            );
        }
    }
}
