#include "texture_cache.h"

TextureCache::TextureCache(boost::filesystem::path graphicsPath)
{
    this->graphicsPath = graphicsPath;
}

SDL_Surface* TextureCache::getTexture(TextureId id)
{
    auto it = textureMap.find(id);
    if (it == textureMap.end())
    {
        SDL_Surface* surface = loadTexture(graphicsPath / getFilename(id));
        textureMap[id] = surface;
        return surface;
    }
    else
    {
        return it->second;
    }
}

TextureCache::~TextureCache()
{
    for (auto it = textureMap.begin(); it != textureMap.end(); it++)
    {
        SDL_FreeSurface(it->second);
        // TODO: USE NULLPTR
        it->second = NULL;
    }
}

SDL_Surface* TextureCache::loadTexture(boost::filesystem::path path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        // TODO: COLLECT ERROR MESSAGE AND THROW EXCEPTION
    }
    return surface;
}