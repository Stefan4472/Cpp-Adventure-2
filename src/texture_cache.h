#ifndef _TEXTURE_CACHE_H
#define _TEXTURE_CACHE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/filesystem.hpp>
#include <unordered_map>
#include <stdexcept>
#include "texture_id.h"

// TODO: REMOVE (DEBUGGING)
#include <iostream>

class TextureCache
{
public:
    TextureCache(
            boost::filesystem::path graphicsPath,
            SDL_Renderer* renderer
    );
    // TODO: Use smart pointers? (may be tough with SDL stuff)
    SDL_Texture* getTexture(TextureId id);
    // Get dimensions of specified texture (width, height)
    std::pair<int, int> getDimensions(TextureId id);
    ~TextureCache();

private:
    boost::filesystem::path graphicsPath;
    SDL_Renderer* renderer;
    std::unordered_map<TextureId, SDL_Texture*> textureMap;
    SDL_Texture* loadTexture(boost::filesystem::path path);
};

#endif