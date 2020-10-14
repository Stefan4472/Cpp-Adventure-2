#ifndef _GAME_CONTEXT_H
#define _GAME_CONTEXT_H

#include <memory>
#include "texture_cache.h"
#include "engine_interface.h"


class GameContext
{
public:
    int screenWidth;
    int screenHeight;
    int tileSizePx;
    std::shared_ptr<TextureCache> textureCache;
    // TODO: MAKE CONST
    EngineInterface* engine;

    GameContext(
        int screenWidth,
        int screenHeight,
        int tileSizePx,
        std::shared_ptr<TextureCache> textureCache,
        EngineInterface* engineInterface
    );
};

#endif