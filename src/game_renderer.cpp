#include "game_renderer.h"

GameRenderer::GameRenderer(
        SDL_Renderer* renderer,
        std::shared_ptr<TextureCache> textureCache,
        int gameWidth,
        int gameHeight
) {
    this->renderer = renderer;
    this->textureCache = textureCache;
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    topLeftWorldX = 0.0;
    topLeftWorldY = 0.0;
}

void GameRenderer::setTopLeftCoord(
        double worldX, 
        double worldY
) {
    topLeftWorldX = worldX;
    topLeftWorldY = worldY;
}

void GameRenderer::drawToWorld(
        TextureId textureId, 
        double worldX, 
        double worldY
) {
    // TODO: INEFFICIENT TO QUERY DIMENSIONS EACH DRAW()
    int texture_width, texture_height;
    std::tie(texture_width, texture_height) = 
        textureCache->getDimensions(textureId);

    SDL_Rect dest = {
        static_cast<int>(worldX - topLeftWorldX),
        static_cast<int>(worldY - topLeftWorldY),
        texture_width,
        texture_height
    };

    SDL_RenderCopy(
        renderer,
        textureCache->getTexture(textureId),
        NULL,
        &dest
    );
}

void GameRenderer::drawToWorld(
        TextureId textureId,
        SDL_Rect& subRect,
        double worldX,
        double worldY
) {
    SDL_Rect dest = {
        static_cast<int>(worldX - topLeftWorldX),
        static_cast<int>(worldY - topLeftWorldY),
        subRect.w,
        subRect.h
    };

    SDL_RenderCopy(
        renderer,
        textureCache->getTexture(textureId),
        &subRect,
        &dest
    );
}