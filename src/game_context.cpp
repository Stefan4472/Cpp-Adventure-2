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