#include "game_engine.h"

GameEngine::GameEngine(
        boost::filesystem::path rootPath,
        int gameWidth,
        int gameHeight)
{
    std::cout << "Init GameEngine with width,height " << gameWidth << ", " << gameHeight << std::endl;
    auto graphics_path = rootPath / "graphics";
    auto map_path = rootPath / "map.txt";

    textureCache = std::make_shared<TextureCache>(
        graphics_path
    );
    
    map = std::make_shared<Map>(
        Map::fromFile(map_path)
    );

    gameContext = std::make_shared<GameContext>(
        gameWidth,
        gameHeight,
        TILE_SIZE_PX,
        textureCache.get(),
        map.get()
    );

    player = std::make_shared<PlayerSprite>(
        gameContext.get(), 
        SpriteType::PLAYER, 
        320, 
        256
    );
}

void GameEngine::inputUpPressed()
{
    inputQueue.push(EventId::PRESS_UP);
}

void GameEngine::inputDownPressed()
{
    inputQueue.push(EventId::PRESS_DOWN);
}

void GameEngine::inputLeftPressed()
{
    inputQueue.push(EventId::PRESS_LEFT);
}

void GameEngine::inputRightPressed()
{
    inputQueue.push(EventId::PRESS_RIGHT);
}

void GameEngine::update()
{
    while (!inputQueue.empty())
    {
        EventId next_input = inputQueue.front();
        handleInput(next_input);
        inputQueue.pop();
    }
}

void GameEngine::handleInput(EventId inputId)
{
    switch (inputId)
    {
        case EventId::PRESS_UP:
        {
            player->moveUp();
            break;
        }
        case EventId::PRESS_DOWN:
        {
            player->moveDown();
            break;
        }
        case EventId::PRESS_LEFT:
        {
            player->moveLeft();
            break;
        }
        case EventId::PRESS_RIGHT:
        {
            player->moveRight();
            break;
        }
        default:
        {
            throw std::invalid_argument("Unsupported EventId");
        }
    }
}

void GameEngine::draw(SDL_Surface* surface)
{
    // Draw tiles
    SDL_Rect source_rect = {0, 0, TILE_SIZE_PX, TILE_SIZE_PX};
    SDL_Rect dest_rect;
    for (int i = 0; i < map->numRows; i++)
    {
        for (int j = 0; j < map->numCols; j++)
        {
            dest_rect.x = j * TILE_SIZE_PX;
            dest_rect.y = i * TILE_SIZE_PX;
            // Look up the TextureId for this tile
            TextureId tile_texture = getTileTextureId(map->mapTiles[i][j]);

            SDL_BlitSurface(
                textureCache->getTexture(tile_texture), 
                &source_rect,
                surface, 
                &dest_rect
            );
        }
    }
    
    // Draw sprite image.
    SDL_Rect src_rect;

    src_rect.w = textureCache->getTexture(TextureId::SPRITE_FRONT)->w;
    src_rect.h = textureCache->getTexture(TextureId::SPRITE_FRONT)->h;

    // Make the image bottom line up with the tile the sprite is on.
    dest_rect.x = 200;
    dest_rect.y = 200;

    SDL_BlitSurface(textureCache->getTexture(TextureId::SPRITE_FRONT), &src_rect, surface, &dest_rect);

    // Draw player
    player->draw(surface);
}