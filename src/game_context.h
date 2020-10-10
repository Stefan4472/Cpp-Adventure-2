#ifndef _GAME_CONTEXT_H
#define _GAME_CONTEXT_H

#include <memory>
#include "texture_cache.h"
#include "map.h"

class GameContext
{
public:
    int screenWidth;
    int screenHeight;
    int tileSizePx;
    std::shared_ptr<TextureCache> textureCache;
    std::shared_ptr<Map> map;

    GameContext(
        int screenWidth,
        int screenHeight,
        int tileSizePx,
        std::shared_ptr<TextureCache> textureCache,
        std::shared_ptr<Map> map
    );

    // Check the Map to see if the tile with the given coordinates
    // can be walked on/stood on.
    bool isTileWalkable(int tileX, int tileY);

    std::pair<int, int> resolveTile(double worldX, double worldY);
};

#endif