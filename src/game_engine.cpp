#include "game_engine.h"

GameEngine::GameEngine(
        boost::filesystem::path rootPath,
        int gameWidth,
        int gameHeight,
        SDL_Renderer* renderer
)
{
    std::cout << "Init GameEngine with width,height " << gameWidth << ", " << gameHeight << std::endl;
    auto graphics_path = rootPath / "graphics";
    auto map_path = rootPath / "map.txt";

    textureCache = std::make_shared<TextureCache>(
        graphics_path,
        renderer
    );
    
    map = std::make_shared<Map>(
        Map::fromFile(map_path)
    );

    gameContext = std::make_shared<GameContext>(
        gameWidth,
        gameHeight,
        TILE_SIZE_PX,
        textureCache,
        map
    );

    player = std::make_shared<PlayerSprite>(
        gameContext, 
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

void GameEngine::draw(SDL_Renderer* renderer)
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
            dest_rect.w = TILE_SIZE_PX;
            dest_rect.h = TILE_SIZE_PX;
            // Look up the TextureId for this tile
            TextureId tile_texture = getTileTextureId(map->mapTiles[i][j]);

            SDL_RenderCopy(
                renderer,
                textureCache->getTexture(tile_texture), 
                NULL, //&source_rect,
                &dest_rect
            );
        }
    }
    
    // SDL_RenderCopy(renderer, textureCache->getTexture(TextureId::SPRITE_FRONT), NULL, NULL);

    // SDL_BlitSurface(
    //     textureCache->getTexture(TextureId::SPRITE_FRONT), 
    //     &source_rect,
    //     surface, 
    //     &dest_rect
    // );
    
    // source_rect.w = TILE_SIZE_PX;
    // source_rect.h = TILE_SIZE_PX;
    // dest_rect.x = 400;
    // dest_rect.y = 400;

    // SDL_BlitSurface(
    //     textureCache->getTexture(TextureId::DIRT_TILE), 
    //     &source_rect, 
    //     surface, 
    //     &dest_rect
    // );

    // Draw player
    player->draw(renderer);
}