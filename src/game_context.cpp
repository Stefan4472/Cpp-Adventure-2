#include "game_context.h"

GameContext::GameContext(
        int screenWidth,
        int screenHeight,
        int tileSizePx,
        TextureCache* textureCache,
        Map* map
)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->tileSizePx = tileSizePx;
    this->textureCache = textureCache;
    this->map = map;
}