#ifndef _GAME_CONTEXT_H
#define _GAME_CONTEXT_H

#include "texture_cache.h"
#include "map.h"

class GameContext
{
public:
    int screenWidth;
    int screenHeight;
    int tileSizePx;
    // TODO: USE SMART POINTER? NULLPTR?
    TextureCache* textureCache;
    Map* map;

    GameContext(
        int screenWidth,
        int screenHeight,
        int tileSizePx,
        TextureCache* textureCache,
        Map* map
    );
};

#endif