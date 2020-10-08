#ifndef _GAME_CONTEXT_H
#define _GAME_CONTEXT_H

#include "texture_cache.h"


struct GameContext
{
    int screenWidth;
    int screenHeight;
    int tileSizePx;
    // TODO: USE SMART POINTER? NULLPTR?
    TextureCache* textureCache;
};

#endif