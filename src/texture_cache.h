#ifndef _TEXTURE_CACHE_H
#define _TEXTURE_CACHE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/filesystem.hpp>
#include <unordered_map>
#include <stdexcept>
#include "texture_id.h"


class TextureCache
{
public:
    TextureCache(boost::filesystem::path graphicsPath);
    // TODO: Use smart pointers? (may be tough with SDL stuff)
    SDL_Surface* getTexture(TextureId id);
    ~TextureCache();

private:
    boost::filesystem::path graphicsPath;
    std::unordered_map<TextureId, SDL_Surface*> textureMap;
    SDL_Surface* loadTexture(boost::filesystem::path path);
};

#endif