#include "texture_cache.h"

TextureCache::TextureCache(boost::filesystem::path graphicsPath)
{
    if (!boost::filesystem::is_directory(graphicsPath))
    {
        throw std::invalid_argument(
            "The provided path is not a directory"
        );
    }
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
        throw std::runtime_error(
            "Couldn't load image: SDL_Error " + std::string(SDL_GetError())
        );
    }
    else
    {
        return surface;
    }
}