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
};

#endif