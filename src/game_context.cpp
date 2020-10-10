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
    // TODO: DOUBLE-CHECK BOUNDS
    return
        tileX >= 0 &&
        tileX < map->numCols &&
        tileY >= 0 &&
        tileY < map->numRows;
}

std::pair<int, int> GameContext::resolveTile(double worldX, double worldY)
{
    return std::make_pair(
        static_cast<int>(worldX) / tileSizePx, 
        static_cast<int>(worldY) / tileSizePx
    );
}

