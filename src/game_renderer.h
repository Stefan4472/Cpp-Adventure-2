#ifndef _GAME_RENDERER_H
#define _GAME_RENDERER_H

#include <SDL2/SDL.h>
#include "texture_cache.h"


class GameRenderer
{
public:
    GameRenderer(
        SDL_Renderer* renderer,
        std::shared_ptr<TextureCache> textureCache,
        int gameWidth,
        int gameHeight
    );
    
    void setTopLeftCoord(
        double worldX, 
        double worldY
    );

    void drawToWorld(
        TextureId textureId, 
        double worldX, 
        double worldY
    );

    void drawToWorld(
        TextureId textureId,
        SDL_Rect& subRect,
        double worldX,
        double worldY
    );

private:
    SDL_Renderer* renderer;
    std::shared_ptr<TextureCache> textureCache;
    int gameWidth, gameHeight;
    double topLeftWorldX, topLeftWorldY;
};

#endif