#include "texture_cache.h"

TextureCache::TextureCache(
        boost::filesystem::path graphicsPath,
        SDL_Renderer* renderer
)
{
    if (!boost::filesystem::is_directory(graphicsPath))
    {
        throw std::invalid_argument(
            "The provided path is not a directory"
        );
    }
    this->graphicsPath = graphicsPath;
    this->renderer = renderer;
}

SDL_Texture* TextureCache::getTexture(TextureId id)
{
    // std::cout << "Looking up texture " << std::to_string(static_cast<int>(id)) << "...";
    auto it = textureMap.find(id);
    if (it == textureMap.end())
    {
        // std::cout << " Not Found" << std::endl;
        SDL_Texture* texture = loadTexture(graphicsPath / getFilename(id));
        textureMap[id] = texture;
        return texture;
    }
    else
    {
        // std::cout << " Found" << std::endl;
        return it->second;
    }
}

std::pair<int, int> TextureCache::getDimensions(TextureId id)
{
    SDL_Texture* texture = getTexture(id);
    int width, height;

    SDL_QueryTexture(
        texture, 
        NULL, 
        NULL, 
        &width, 
        &height
    );

    return std::make_pair(width, height);
}

TextureCache::~TextureCache()
{
    for (auto it = textureMap.begin(); it != textureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
        // TODO: USE NULLPTR
        it->second = NULL;
    }
}

SDL_Texture* TextureCache::loadTexture(boost::filesystem::path path)
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
        SDL_Texture* texture = SDL_CreateTextureFromSurface(
            renderer, 
            surface
        );
        
        if (texture == NULL)
        {
            throw std::runtime_error(
                "Couldn't create texture: SDL_Error " + std::string(SDL_GetError())
            );
        }

        // Free surface (no longer needed)
        SDL_FreeSurface(surface);

        return texture;
    }
}