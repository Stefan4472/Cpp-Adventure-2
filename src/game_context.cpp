#include "game_context.h"

GameContext::GameContext(
        int screenWidth,
        int screenHeight,
        int tileSizePx,
        std::shared_ptr<TextureCache> textureCache,
        std::shared_ptr<Map> map
)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->tileSizePx = tileSizePx;
    this->textureCache = textureCache;
    this->map = map;
}

bool GameContext::isTileWalkable(int tileX, int tileY)
{
    // Check bounds
    if (!map->isTileWithinMap(tileX, tileY))
    {
        return false;
    }
    // Get object (if any) on desired tile
    std::shared_ptr<MapObject> object_on_tile =
        map->getObjectAtTile(tileX, tileY);
    // Check if object exists and isn't walkable
    if (object_on_tile && !object_on_tile->getIsWalkable())
    {
        return false;
    }
    // Otherwise, we're good!
    return true;
}

std::pair<int, int> GameContext::resolveTile(double worldX, double worldY)
{
    return std::make_pair(
        static_cast<int>(worldX) / tileSizePx, 
        static_cast<int>(worldY) / tileSizePx
    );
}

